// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

extern int32_t g_UnderThreshold_mC_s32;
extern int32_t g_OverThreshold_mC_s32;
extern int32_t g_Hyst_mC_s32;
extern TempMon_sts_e Sts_e;

void setUp(void)
{
  Sts_e = TEMPMON_STS_NORMAL;

  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 2000;
}

void tearDown(void)
{}

void test_TempMon_Run_NORMAL_to_OVER_TransitionAboveThreshold(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(90000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_to_UNDER_TransitionBelowThreshold(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(-5000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_StaysNormalWithinThresholds(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(25000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_AtOverThresholdBoundaryStaysNormal(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(85000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_JustAboveOverThresholdTransitionsToOVER(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(85001);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_AtUnderThresholdBoundaryStaysNormal(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(0);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(100), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_NORMAL_JustBelowUnderThresholdTransitionsToUNDER(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(-1);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_UNDER_StaysUnderBelowThreshold(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(-10000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(127), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_UNDER_to_NORMAL_TransitionAboveHysteresisThreshold(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(2001);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_UNDER_AtHysteresisThresholdStaysUnder(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(2000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_UNDER_StaysUnderBetweenUnderAndHysteresis(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(1000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_OVER_StaysOverAboveThreshold(void)
{
  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(95000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_OVER_to_NORMAL_TransitionBelowHysteresisThreshold(void)
{
  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(82999);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_OVER_AtHysteresisThresholdStaysOver(void)
{
  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(83000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(209), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_OVER_StaysOverBetweenOverAndHysteresis(void)
{
  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(84000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(222), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_HysteresisPreventOscillationAtUnderThreshold(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  TempMon_Run(500);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(235), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(1500);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(239), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_HysteresisPreventOscillationAtOverThreshold(void)
{
  Sts_e = TEMPMON_STS_OVER;

  TempMon_Run(84500);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(250), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(
      84999);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(255), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_SequentialTransitions_NORMAL_OVER_NORMAL(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(264), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(86000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(268), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(84000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(272), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(82999);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(276), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_SequentialTransitions_NORMAL_UNDER_NORMAL(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(-1000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(1000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(291), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(2001);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(295), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_MultipleCyclesNormalOver(void)
{
  TempMon_Run(90000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(304), UNITY_DISPLAY_STYLE_INT);
  TempMon_Run(82999);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(306), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(86000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(310), UNITY_DISPLAY_STYLE_INT);
  TempMon_Run(82999);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(312), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_CustomThresholdAndHysteresis(void)
{
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 30000;
  g_Hyst_mC_s32 = 5000;

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(324), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(35000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(328), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(25000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(332), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(24999);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(336), UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_ExtremeTemperatureValues(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(343), UNITY_DISPLAY_STYLE_INT);

  TempMon_Run(-100000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(347), UNITY_DISPLAY_STYLE_INT);

  Sts_e = TEMPMON_STS_NORMAL;

  TempMon_Run(150000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(354), UNITY_DISPLAY_STYLE_INT);
}