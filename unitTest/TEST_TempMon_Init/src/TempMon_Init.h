#ifndef TEST_TEMPMON_INIT_H
#define TEST_TEMPMON_INIT_H

#include "TempMon.h"

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
 *   temp_mC.
 *
 * This guarantees that the initial state respects the configured thresholds
 * and hysteresis rules (no special “startup” behavior is applied).
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature    | Param |
 * Data factor | Data offset | Data size | Data range             | Data unit |
 * |-------------------------|:--:|:---:|--------------------------|:-----:|------------:|------------:|----------:|------------------------|----------|
 * | temp_mC                 | X  |     | int32_t                  |   X   | 1 |
 * 0 |         1 | implementation-defined | [mdegC]  | | g_UnderThreshold_mC_s32
 * | X  |     | int32_t (extern)         |   -   |           1 |           0 |
 * 1 | implementation-defined | [mdegC]  | | g_OverThreshold_mC_s32  | X  | |
 * int32_t (extern)         |   -   |           1 |           0 |         1 |
 * implementation-defined | [mdegC]  | | g_Hyst_mC_s32           | X  |     |
 * int32_t (extern)         |   -   |           1 |           0 |         1 |
 * typically >= 0         | [mdegC]  |
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
 * Current temperature in milli-degC (mdegC) used to set the initial state.
 *
 * @return void
 */
void TempMon_Init(int32_t temp_mC);

TempMon_sts_e get_Sts_e(void);
void set_Sts_e(TempMon_sts_e val);

#endif /* TEST_TEMPMON_INIT_H */
