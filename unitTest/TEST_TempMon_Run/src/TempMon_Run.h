#ifndef BUILDTBL_H
#define BUILDTBL_H

#include <stdint.h>

/**
 * @brief Run one update step of the temperature monitor.
 *
 * @details
 * **Goal of the function**
 *
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature     | Param | Data factor | Data offset | Data size | Data range                          | Unit   |
 * |------------------------|:--:|:---:|----------------------------|:-----:|------------:|------------:|----------:|-------------------------------------|--------|
 * | temp_mC                | X  |     | int32_t                    | X     | 1           | 0           | 1         | [SINT32_MIN,SINT32_MAX]             | mdegC  |
 * | g_UnderThreshold_mC_s32| X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | [SINT32_MIN,SINT32_MAX]             | mdegC  |
 * | g_OverThreshold_mC_s32 | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | [SINT32_MIN,SINT32_MAX]             | mdegC  |
 * | g_Hyst_mC_s32          | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | [SINT32_MIN,SINT32_MAX]             | mdegC  |
 * | Sts_e                  | X  |  X  | TempMon_sts_e (static)     | -     | 1           | 0           | 1         | TEMPMON_STS_NORMAL / _UNDER / _OVER | -      |
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

#endif