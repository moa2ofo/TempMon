// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

void resetVar(TempMon_sts_e l_Sts_e, int32_t l_UnderThreshold_mC_s32, int32_t l_OverThreshold_mC_s32, int32_t l_Hyst_mC_s32)
{
  l_Sts_e = TEMPMON_STS_NORMAL;
  l_UnderThreshold_mC_s32 = 0;
  l_OverThreshold_mC_s32 = 0;
  l_Hyst_mC_s32 = 0;
}

void assertVar(TempMon_sts_e expected_sts, int32_t expected_under, int32_t expected_over, int32_t expected_hyst)
{
  UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((expected_sts)), (UNITY_INT)(UNITY_INT32)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_INT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((expected_under)), (UNITY_INT)(UNITY_INT32)((g_UnderThreshold_mC_s32)), (
 ((void *)0)
 ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((expected_over)), (UNITY_INT)(UNITY_INT32)((g_OverThreshold_mC_s32)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((expected_hyst)), (UNITY_INT)(UNITY_INT32)((g_Hyst_mC_s32)), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT32);
}

void setUp(void)
{
  resetVar(0, 0, 0, 0);
}

void tearDown(void)
{}

void test_NORMAL_state_remains_NORMAL_when_temp_in_range(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(25000);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_NORMAL_to_UNDER_transition(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(3000);

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

void test_NORMAL_to_OVER_transition(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(45000);

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

void test_NORMAL_state_at_under_threshold_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(5000);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_NORMAL_state_at_over_threshold_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(40000);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_UNDER_state_remains_UNDER_when_temp_below_hysteresis(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(6000);

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

void test_UNDER_to_NORMAL_transition_with_hysteresis(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(7500);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_UNDER_state_at_hysteresis_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(7000);

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

void test_UNDER_state_just_above_hysteresis_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(7001);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_OVER_state_remains_OVER_when_temp_above_hysteresis(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(39000);

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

void test_OVER_to_NORMAL_transition_with_hysteresis(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(37000);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_OVER_state_at_hysteresis_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(38000);

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

void test_OVER_state_just_below_hysteresis_boundary(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(37999);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_cycle_NORMAL_to_UNDER_back_to_NORMAL(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(3000);
  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);

  TempMon_Run(8000);
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_cycle_NORMAL_to_OVER_back_to_NORMAL(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(45000);
  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);

  TempMon_Run(36000);
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

void test_zero_hysteresis_UNDER_to_NORMAL(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 0;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(5001);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 0);
}

void test_zero_hysteresis_OVER_to_NORMAL(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 0;

  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(39999);

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 0);
}

void test_large_hysteresis_UNDER_to_NORMAL(void)
{
  g_UnderThreshold_mC_s32 = 5000;
  g_OverThreshold_mC_s32 = 40000;
  g_Hyst_mC_s32 = 5000;

  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(9999);
  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 5000);

  TempMon_Run(10001);
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 5000);
}

void test_negative_temperatures(void)
{
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(-15000);
  assertVar(TEMPMON_STS_UNDER, -10000, 50000, 2000);
}