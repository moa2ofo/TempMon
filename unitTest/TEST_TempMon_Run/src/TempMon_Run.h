#ifndef BUILDTBL_H
#define BUILDTBL_H

#include <stdint.h>

/**
 * @brief Run one update step of the temperature monitor.
 *
 * @details
 * Update the internal state machine based on the latest temperature sample.
 *
 * Processing logic:
 * - If current state is TEMPMON_STS_NORMAL:
 *   - Enter TEMPMON_STS_UNDER if `temp_mC < g_UnderThreshold_mC_s32`.
 *   - Else enter TEMPMON_STS_OVER if `temp_mC > g_OverThreshold_mC_s32`.
 *   - Else remain TEMPMON_STS_NORMAL.
 * - If current state is TEMPMON_STS_UNDER:
 *   - Return to TEMPMON_STS_NORMAL if `temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)`.
 *   - Else remain TEMPMON_STS_UNDER.
 * - If current state is TEMPMON_STS_OVER:
 *   - Return to TEMPMON_STS_NORMAL if `temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)`.
 *   - Else remain TEMPMON_STS_OVER.
 *
 * @par Interface summary
 *
 * | Interface               | In | Out | Data type / Signature     | Param | Data factor | Data offset | Data size | Data range                                           | Unit   |
 * |------------------------|:--:|:---:|----------------------------|:-----:|------------:|------------:|----------:|------------------------------------------------------|--------|
 * | temp_mC                | X  |     | int32_t                    | X     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_UnderThreshold_mC_s32| X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_OverThreshold_mC_s32 | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | implementation-defined                                | mdegC  |
 * | g_Hyst_mC_s32          | X  |     | int32_t (extern)           | -     | 1           | 0           | 1         | typically >= 0                                        | mdegC  |
 * | Sts_e                  | X  |  X  | TempMon_sts_e (static)     | -     | -           | -           | -         | TEMPMON_STS_NORMAL / _UNDER / _OVER                   | -      |
 *
 * @param temp_mC Current temperature in milli-degC.
 * @return void
 */
void TempMon_Run(int32_t temp_mC);

#endif