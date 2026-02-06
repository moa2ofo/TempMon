// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

static void reset_globals_and_statics(void)
{
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 0;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);
}

void setUp(void)
{ reset_globals_and_statics(); }

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_just_below_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(999);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_exactly_at_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(1000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_just_above_UnderThreshold_below_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(1001);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_just_above_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(5001);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_exactly_at_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(5000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_just_below_OverThreshold_above_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(4999);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_just_above_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(1101);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_UNDER_when_temp_exactly_at_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(1100);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_UNDER_when_temp_just_below_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(1099);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_just_below_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(4899);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_OVER_when_temp_exactly_at_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(4900);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(145), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_in_OVER_when_temp_just_above_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 5000;
  g_Hyst_mC_s32 = 100;

  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(4901);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((TempMon_GetSts())), (
 ((void *)0)
 ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);
}