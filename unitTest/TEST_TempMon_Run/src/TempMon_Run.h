#ifndef TEST_TEMPMON_RUN_H
#define TEST_TEMPMON_RUN_H

#include "TempMon.h"
#include "TempMon_priv.h"

/**
 * @brief Run one update step of the temperature monitor.
 *
 * @details
 * **Goal of the function**
 *
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature     | Param | Data factor | Data offset | Data size | Data range                                           | Unit   |
 * |------------------------|:--:|:---:|----------------------------|:-----:|------------:|------------:|----------:|------------------------------------------------------|--------|
 * | temp_mC                | X  |     | int32_t                    | X     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_UnderThreshold_mC_s32| X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_OverThreshold_mC_s32 | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_Hyst_mC_s32          | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | typically >= 0                                        | mdegC  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (Sts_e == TEMPMON_STS_NORMAL) then (yes)
 *   if (temp_mC <  g_UnderThreshold_mC_s32) then (yes)
 *     :Sts_e = TEMPMON_STS_UNDER;
 *   else (no)
 *     if (temp_mC > g_OverThreshold_mC_s32) then (yes)
 *       :Sts_e = TEMPMON_STS_OVER;
 *     else (no)
 *       :stay TEMPMON_STS_NORMAL;
 *     endif
 *   endif
 * elseif (Sts_e == TEMPMON_STS_UNDER) then (yes)
 *   if (temp_mC >  g_UnderThreshold_mC_s32 + g_Hyst_mC_s32) then (yes)
 *     :Sts_e = TEMPMON_STS_NORMAL;
 *   else (no)
 *     :stay TEMPMON_STS_UNDER;
 *   endif
 * else (TEMPMON_STS_OVER)
 *   if (temp_mC < g_OverThreshold_mC_s32 - g_Hyst_mC_s32) then (yes)
 *     :Sts_e = TEMPMON_STS_NORMAL;
 *   else (no)
 *     :stay TEMPMON_STS_OVER;
 *   endif
 * endif
 * stop
 * @enduml
 *
 * @param temp_mC
 * Current temperature in milli-degC (mdegC).
 *
 * @return void
 */
void TempMon_Run(int32_t temp_mC);


#endif /* TEST_TEMPMON_RUN_H */