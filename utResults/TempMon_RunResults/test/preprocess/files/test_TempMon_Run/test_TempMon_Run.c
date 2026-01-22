// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

void setUp(void)
{
  Sts_e = TEMPMON_STS_NORMAL;
}

void tearDown(void)
{}

void test_InitialStateIsNormal(void)
{
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalStateRemainsNormalWhenNoThresholdCrossed(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(27, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(28, 0,
 0
 );

  TempMon_Run(0);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalToUnderTransition(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(40, -5000,
 1
 );

  TempMon_Run(-5000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalToOverTransition(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(52, 50000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(53, 50000,
 1
 );

  TempMon_Run(50000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalPrioritizesUnderOverOver(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(66, 25000,
 1
 );

  TempMon_Run(25000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);
}

void test_UnderStateRemainsUnderWhenNoExit(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  IsUnderExit_b_CMockExpectAndReturn(83, -3000,
 0
 );

  TempMon_Run(-3000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_INT);
}

void test_UnderToNormalTransitionWithHysteresis(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  IsUnderExit_b_CMockExpectAndReturn(98, 2000,
 1
 );

  TempMon_Run(2000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);
}

void test_OverStateRemainsOverWhenNoExit(void)
{
  Sts_e = TEMPMON_STS_OVER;

  IsOverExit_b_CMockExpectAndReturn(115, 45000,
 0
 );

  TempMon_Run(45000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_INT);
}

void test_OverToNormalTransitionWithHysteresis(void)
{
  Sts_e = TEMPMON_STS_OVER;

  IsOverExit_b_CMockExpectAndReturn(130, 30000,
 1
 );

  TempMon_Run(30000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_INT);
}

void test_CompleteCycleNormalUnderNormal(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(144, -6000,
 1
 );
  TempMon_Run(-6000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(149, -4000,
 0
 );
  TempMon_Run(-4000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(154, 1000,
 1
 );
  TempMon_Run(1000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT);
}

void test_CompleteCycleNormalOverNormal(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(164, 55000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(165, 55000,
 1
 );
  TempMon_Run(55000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(167), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(170, 52000,
 0
 );
  TempMon_Run(52000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(175, 40000,
 1
 );
  TempMon_Run(40000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_INT);
}

void test_MultipleTransitionsSequence(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(186, -10000,
 1
 );
  TempMon_Run(-10000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(191, 5000,
 1
 );
  TempMon_Run(5000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(196, 60000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(197, 60000,
 1
 );
  TempMon_Run(60000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(202, 35000,
 1
 );
  TempMon_Run(35000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(204), UNITY_DISPLAY_STYLE_INT);
}

void test_ConsecutiveCallsSameState(void)
{
  Sts_e = TEMPMON_STS_NORMAL;

  IsUnderEnter_b_CMockExpectAndReturn(216, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(217, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(222, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(223, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(225), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(228, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(229, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_INT);
}

void test_ExtremeLowTemperature(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(239, -100000,
 1
 );

  TempMon_Run(-100000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(243), UNITY_DISPLAY_STYLE_INT);
}

void test_ExtremeHighTemperature(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(251, 100000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(252, 100000,
 1
 );

  TempMon_Run(100000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(256), UNITY_DISPLAY_STYLE_INT);
}

void test_ZeroTemperatureInNormalState(void)
{
  Sts_e = TEMPMON_STS_NORMAL;

  IsUnderEnter_b_CMockExpectAndReturn(265, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(266, 0,
 0
 );

  TempMon_Run(0);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(270), UNITY_DISPLAY_STYLE_INT);
}