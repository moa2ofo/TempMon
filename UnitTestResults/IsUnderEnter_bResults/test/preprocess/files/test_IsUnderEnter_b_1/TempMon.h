// CEEDLING NOTICE: This generated file only to be consumed by CMock

#ifndef _TEMPMON_H_ // Ceedling-generated include guard
#define _TEMPMON_H_

typedef enum { TEMPMON_STS_NORMAL = 0, TEMPMON_STS_UNDER, TEMPMON_STS_OVER } TempMon_sts_e;
extern int32_t g_UnderThreshold_mC_s32;
extern int32_t g_OverThreshold_mC_s32;
extern int32_t g_Hyst_mC_s32;
void TempMon_Init(int32_t temp_mC);
static void TempMon_Run(int32_t temp_mC);
TempMon_sts_e TempMon_GetSts(void);

_Bool
    TempMon_IsUnderAlv_b(void);

_Bool
    TempMon_IsOverAlv_b(void);

#endif // _TEMPMON_H_
