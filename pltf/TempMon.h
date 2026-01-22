/* TempMon.h */

#ifndef TEMPMON_H
#define TEMPMON_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @file TempMon.h
 * @brief Temperature monitoring module (under/over detection with hysteresis).
 *
 * @details
 * **Goal of the module**
 *
 * Provide a small state machine to classify an input temperature into:
 * - **NORMAL**
 * - **UNDER** (below configured under-threshold)
 * - **OVER**  (above configured over-threshold)
 *
 * The module applies **hysteresis** to avoid rapid toggling near thresholds:
 * - Enter **UNDER** when `temp_mC < g_UnderThreshold_mC_s32`
 * - Exit  **UNDER** when `temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)`
 * - Enter **OVER**  when `temp_mC > g_OverThreshold_mC_s32`
 * - Exit  **OVER**  when `temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)`
 *
 * @par Units
 * All temperatures are expressed in **milli-degC (m°C)**:
 * - Example: `85000` = `85.000 °C`
 *
 * @par Typical usage
 * - Set the public configuration variables (thresholds, hysteresis).
 * - Call TempMon_Init() once at startup with the current temperature.
 * - Call TempMon_Run() periodically with the current temperature.
 * - Read the state with TempMon_GetSts() or the convenience functions.
 *
 * @par Notes and limitations
 * - The module does not validate configuration ranges; ensure coherent values
 *   (e.g., positive hysteresis, under < over).
 * - The module does not implement timing filters (activation/deactivation
 * delays).
 */

/* ===== Public types ===== */

/**
 * @brief Temperature monitor state.
 *
 * @details
 * The temperature monitor state machine can be in one of the following states:
 * - #TEMPMON_STS_NORMAL: temperature is within thresholds (considering
 * hysteresis exits)
 * - #TEMPMON_STS_UNDER: under-temperature condition is active
 * - #TEMPMON_STS_OVER:  over-temperature condition is active
 */
typedef enum {
  TEMPMON_STS_NORMAL = 0,
  TEMPMON_STS_UNDER,
  TEMPMON_STS_OVER
} TempMon_sts_e;

/* ===== Public configuration (extern) =====
 * Units: milli-degC (m°C)
 * Example: 85000 = 85.000 °C
 */

/**
 * @brief Under-temperature threshold in m°C.
 *
 * @details
 * If the module is in NORMAL state, it enters UNDER when:
 * - `temp_mC < g_UnderThreshold_mC_s32`
 *
 * If the module is in UNDER state, it returns to NORMAL when:
 * - `temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)`
 */
extern int32_t g_UnderThreshold_mC_s32;

/**
 * @brief Over-temperature threshold in m°C.
 *
 * @details
 * If the module is in NORMAL state, it enters OVER when:
 * - `temp_mC > g_OverThreshold_mC_s32`
 *
 * If the module is in OVER state, it returns to NORMAL when:
 * - `temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)`
 */
extern int32_t g_OverThreshold_mC_s32;

/**
 * @brief Hysteresis in m°C applied to both UNDER and OVER transitions.
 *
 * @details
 * Hysteresis is used to avoid state chatter around thresholds:
 * - UNDER exit uses `UnderThreshold + Hyst`
 * - OVER  exit uses `OverThreshold - Hyst`
 *
 * @note
 * Use a non-negative value. A negative hysteresis inverts the intended
 * behavior.
 */
extern int32_t g_Hyst_mC_s32;

/* ===== Public API ===== */

/**
 * @brief Initialize the temperature monitor internal state.
 *
 * @details
 * **Goal of the function**
 *
 * Initialize the internal state machine so that the module starts in a state
 * consistent with the current temperature.
 *
 * The processing logic:
 * - Sets the internal state to #TEMPMON_STS_NORMAL.
 * - Executes the same decision logic used by TempMon_Run() once using @p
 * temp_mC.
 *
 * This guarantees that the initial state respects the configured thresholds
 * and hysteresis rules (no special “startup” behavior is applied).
 *
 * @par Interface summary
 *
 * | Interface                  | In | Out | Data type / Signature | Param |
 * Data factor | Data offset | Data size | Data range                 | Data
 * unit |
 * |---------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                   | X  |     | int32_t                |   X   | 1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_UnderThreshold_mC_s32   | X  |     | int32_t (extern)       |   -   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | |
 * g_OverThreshold_mC_s32    | X  |     | int32_t (extern)       |   -   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | | g_Hyst_mC_s32
 * | X  |     | int32_t (extern)       |   -   |      1      |      0      | 1
 * | typically >= 0             | [m°C]    |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :Sts_e = TEMPMON_STS_NORMAL;
 * :TempMon_Run(temp_mC);
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C) used to set the initial state.
 *
 * @return void
 */
void TempMon_Init(int32_t temp_mC);

/**
 * @brief Run one update step of the temperature monitor.
 *
 * @details
 * **Goal of the function**
 *
 * Update the internal state machine based on the latest temperature sample.
 *
 * The processing logic:
 * - If current state is NORMAL:
 *   - Enter UNDER if `temp_mC < g_UnderThreshold_mC_s32`.
 *   - Else enter OVER if `temp_mC > g_OverThreshold_mC_s32`.
 *   - Else remain NORMAL.
 * - If current state is UNDER:
 *   - Return to NORMAL if `temp_mC > (g_UnderThreshold_mC_s32 +
 * g_Hyst_mC_s32)`.
 *   - Else remain UNDER.
 * - If current state is OVER:
 *   - Return to NORMAL if `temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)`.
 *   - Else remain OVER.
 *
 * @par Interface summary
 *
 * | Interface                  | In | Out | Data type / Signature | Param |
 * Data factor | Data offset | Data size | Data range                 | Data
 * unit |
 * |---------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                   | X  |     | int32_t                |   X   | 1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_UnderThreshold_mC_s32   | X  |     | int32_t (extern)       |   -   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | |
 * g_OverThreshold_mC_s32    | X  |     | int32_t (extern)       |   -   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | | g_Hyst_mC_s32
 * | X  |     | int32_t (extern)       |   -   |      1      |      0      | 1
 * | typically >= 0             | [m°C]    | | TempMon internal status   | X  |
 * X  | TempMon_sts_e (static) |   -   |      -      |      -      |     -     |
 * NORMAL/UNDER/OVER          | [-]      |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (Sts_e == NORMAL) then (yes)
 *   if (temp_mC < UnderThr) then (yes)
 *     :Sts_e = UNDER;
 *   else (no)
 *     if (temp_mC > OverThr) then (yes)
 *       :Sts_e = OVER;
 *     else (no)
 *       :stay NORMAL;
 *     endif
 *   endif
 * elseif (Sts_e == UNDER) then (yes)
 *   if (temp_mC > UnderThr + Hyst) then (yes)
 *     :Sts_e = NORMAL;
 *   else (no)
 *     :stay UNDER;
 *   endif
 * else (OVER)
 *   if (temp_mC < OverThr - Hyst) then (yes)
 *     :Sts_e = NORMAL;
 *   else (no)
 *     :stay OVER;
 *   endif
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C).
 *
 * @return void
 */
void TempMon_Run(int32_t temp_mC);

/**
 * @brief Get the current status of the temperature monitor.
 *
 * @details
 * **Goal of the function**
 *
 * Provide read access to the internal state machine status updated by
 * TempMon_Init() and TempMon_Run().
 *
 * The processing logic:
 * - Returns the current internal state value.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range                     | Data unit
 * |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|--------------------------------|----------|
 * | TempMon internal status | X  |  X  | TempMon_sts_e          |   -   | - |
 * -      |     -     | NORMAL / UNDER / OVER          | [-]      |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :return Sts_e;
 * stop
 * @enduml
 *
 * @return
 * Current temperature monitor status (#TempMon_sts_e).
 */
TempMon_sts_e TempMon_GetSts(void);

/**
 * @brief Convenience check: returns true if status is UNDER.
 *
 * @details
 * **Goal of the function**
 *
 * Provide a boolean helper to quickly check whether the under-temperature
 * condition is currently active.
 *
 * The processing logic:
 * - Compares internal state to #TEMPMON_STS_UNDER.
 * - Returns true if equal, otherwise false.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|------------|----------|
 * | TempMon internal status | X  |  X  | bool                   |   -   | - |
 * -      |     -     | {false,true} | [-]   |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (Sts_e == UNDER) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @return
 * true if under-temperature is active, false otherwise.
 */
bool TempMon_IsUnderAlv_b(void);

/**
 * @brief Convenience check: returns true if status is OVER.
 *
 * @details
 * **Goal of the function**
 *
 * Provide a boolean helper to quickly check whether the over-temperature
 * condition is currently active.
 *
 * The processing logic:
 * - Compares internal state to #TEMPMON_STS_OVER.
 * - Returns true if equal, otherwise false.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|------------|----------|
 * | TempMon internal status | X  |  X  | bool                   |   -   | - |
 * -      |     -     | {false,true} | [-]   |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (Sts_e == OVER) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @return
 * true if over-temperature is active, false otherwise.
 */
bool TempMon_IsOverAlv_b(void);

#endif /* TEMPMON_H */
