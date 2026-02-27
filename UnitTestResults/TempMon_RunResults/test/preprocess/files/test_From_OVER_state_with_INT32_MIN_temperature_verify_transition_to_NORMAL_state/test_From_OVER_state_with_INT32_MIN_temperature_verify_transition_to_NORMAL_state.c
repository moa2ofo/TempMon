// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

void setUp(void)
{
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 0;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);
}

void tearDown(void)
{
}

void test_From_OVER_state_with_INT32_MIN_temperature_verify_transition_to_NORMAL_state(void)
{
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(
             (-2147483647-1)
                      );

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts_e())), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);
}