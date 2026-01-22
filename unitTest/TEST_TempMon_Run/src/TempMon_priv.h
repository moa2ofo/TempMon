/* TempMon_Priv.h */

#ifndef TEMPMON_PRIV_H
#define TEMPMON_PRIV_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @file TempMon_Priv.h
 * @brief Private interface for TempMon module (cfile-static state and helpers).
 *
 * @details
 * **Goal of this header**
 *
 * Provide internal-only declarations used by `TempMon.c` to implement the
 * temperature monitoring state machine. This header is not part of the public
 * API and must not be included by external modules.
 *
 * The private interface contains:
 * - The module internal state variable (#Sts_e).
 * - Helper functions implementing threshold comparisons for state transitions
 *   with hysteresis:
 *   - Enter/Exit **UNDER**
 *   - Enter/Exit **OVER**
 *
 * @par Design notes
 * - All entities declared here are intended to be **file-static** (internal
 * linkage).
 * - The state machine is maintained in `TempMon.c`; this header only
 * centralizes private declarations to keep the `.c` file readable.
 *
 * @par Safety and correctness
 * - The helper functions assume that configuration variables
 *   (`g_UnderThreshold_mC_s32`, `g_OverThreshold_mC_s32`, `g_Hyst_mC_s32`) are
 *   correctly initialized by the application.
 * - No range checks are performed here; negative hysteresis or inconsistent
 *   thresholds may lead to unexpected behavior.
 */

/* ===== Private (file-static) state ===== */

/* ===== Private (cfile-static) functions ===== */

/**
 * @brief Check the entry condition for UNDER state.
 *
 * @details
 * **Goal of the function**
 *
 * Determine whether the temperature sample requires a transition from
 * NORMAL to UNDER.
 *
 * The processing logic:
 * - Returns true when `temp_mC < g_UnderThreshold_mC_s32`.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range                 | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                 | X  |     | int32_t                |   X   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | |
 * g_UnderThreshold_mC_s32 | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (temp_mC < g_UnderThreshold_mC_s32) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C).
 *
 * @return
 * true if the UNDER entry condition is met, false otherwise.
 */
bool IsUnderEnter_b(int32_t temp_mC);

/**
 * @brief Check the exit condition for UNDER state (hysteresis release).
 *
 * @details
 * **Goal of the function**
 *
 * Determine whether the temperature sample requires a transition from
 * UNDER back to NORMAL.
 *
 * The processing logic:
 * - Returns true when `temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)`.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range                 | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                 | X  |     | int32_t                |   X   | 1 |
 * 0      |     1     | implementation-defined     | [m°C]    | |
 * g_UnderThreshold_mC_s32 | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_Hyst_mC_s32           | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | typically >= 0             | [m°C]    |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C).
 *
 * @return
 * true if the UNDER exit condition is met, false otherwise.
 */
bool IsUnderExit_b(int32_t temp_mC);

/**
 * @brief Check the entry condition for OVER state.
 *
 * @details
 * **Goal of the function**
 *
 * Determine whether the temperature sample requires a transition from
 * NORMAL to OVER.
 *
 * The processing logic:
 * - Returns true when `temp_mC > g_OverThreshold_mC_s32`.
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range                 | Data unit |
 * |------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                | X  |     | int32_t                |   X   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_OverThreshold_mC_s32 | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (temp_mC > g_OverThreshold_mC_s32) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C).
 *
 * @return
 * true if the OVER entry condition is met, false otherwise.
 */
bool IsOverEnter_b(int32_t temp_mC);

/**
 * @brief Check the exit condition for OVER state (hysteresis release).
 *
 * @details
 * **Goal of the function**
 *
 * Determine whether the temperature sample requires a transition from
 * OVER back to NORMAL.
 *
 * The processing logic:
 * - Returns true when `temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)`.
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range                 | Data unit |
 * |------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------|----------|
 * | temp_mC                | X  |     | int32_t                |   X   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_OverThreshold_mC_s32 | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | implementation-defined     | [m°C]    | |
 * g_Hyst_mC_s32          | X  |     | int32_t (extern)       |   -   |      1
 * |      0      |     1     | typically >= 0             | [m°C]    |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (m°C).
 *
 * @return
 * true if the OVER exit condition is met, false otherwise.
 */
bool IsOverExit_b(int32_t temp_mC);

#endif /* TEMPMON_PRIV_H */
