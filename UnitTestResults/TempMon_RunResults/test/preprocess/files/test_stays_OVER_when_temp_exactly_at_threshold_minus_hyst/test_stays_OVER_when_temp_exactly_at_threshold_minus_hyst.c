// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

static TempMon_sts_e TempMon_GetSts_State;
static void TempMon_SetSts(TempMon_sts_e sts)
{
  TempMon_GetSts_State = sts;
}
static TempMon_sts_e TempMon_GetSts_Get(void)
{
  return TempMon_GetSts_State;
}

void setUp(void)
{
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 0;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_stays_OVER_when_temp_exactly_at_threshold_minus_hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 200;
  TempMon_SetSts(TEMPMON_STS_OVER);

  TempMon_Run(4800);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((TempMon_GetSts_Get())), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);
}