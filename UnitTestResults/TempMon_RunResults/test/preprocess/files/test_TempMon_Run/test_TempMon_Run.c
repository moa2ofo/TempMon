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
{ UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
                                      ((void *)0)
                                      ), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_INT); }

void test_NormalStateRemainsNormalWhenNoThresholdCrossed(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(25, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(26, 0,
 0
 );

  TempMon_Run(0);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalToUnderTransition(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(38, -5000,
 1
 );

  TempMon_Run(-5000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalToOverTransition(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(50, 50000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(51, 50000,
 1
 );

  TempMon_Run(50000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);
}

void test_NormalPrioritizesUnderOverOver(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(64, 25000,
 1
 );

  TempMon_Run(25000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT);
}

void test_UnderStateRemainsUnderWhenNoExit(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  IsUnderExit_b_CMockExpectAndReturn(81, -3000,
 0
 );

  TempMon_Run(-3000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);
}

void test_UnderToNormalTransitionWithHysteresis(void)
{
  Sts_e = TEMPMON_STS_UNDER;

  IsUnderExit_b_CMockExpectAndReturn(96, 2000,
 1
 );

  TempMon_Run(2000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(100), UNITY_DISPLAY_STYLE_INT);
}

void test_OverStateRemainsOverWhenNoExit(void)
{
  Sts_e = TEMPMON_STS_OVER;

  IsOverExit_b_CMockExpectAndReturn(113, 45000,
 0
 );

  TempMon_Run(45000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(117), UNITY_DISPLAY_STYLE_INT);
}

void test_OverToNormalTransitionWithHysteresis(void)
{
  Sts_e = TEMPMON_STS_OVER;

  IsOverExit_b_CMockExpectAndReturn(128, 30000,
 1
 );

  TempMon_Run(30000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);
}

void test_CompleteCycleNormalUnderNormal(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(142, -6000,
 1
 );
  TempMon_Run(-6000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(147, -4000,
 0
 );
  TempMon_Run(-4000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(152, 1000,
 1
 );
  TempMon_Run(1000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_INT);
}

void test_CompleteCycleNormalOverNormal(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(162, 55000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(163, 55000,
 1
 );
  TempMon_Run(55000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(168, 52000,
 0
 );
  TempMon_Run(52000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(173, 40000,
 1
 );
  TempMon_Run(40000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(175), UNITY_DISPLAY_STYLE_INT);
}

void test_MultipleTransitionsSequence(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(184, -10000,
 1
 );
  TempMon_Run(-10000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(186), UNITY_DISPLAY_STYLE_INT);

  IsUnderExit_b_CMockExpectAndReturn(189, 5000,
 1
 );
  TempMon_Run(5000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(194, 60000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(195, 60000,
 1
 );
  TempMon_Run(60000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(197), UNITY_DISPLAY_STYLE_INT);

  IsOverExit_b_CMockExpectAndReturn(200, 35000,
 1
 );
  TempMon_Run(35000);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(202), UNITY_DISPLAY_STYLE_INT);
}

void test_ConsecutiveCallsSameState(void)
{
  Sts_e = TEMPMON_STS_NORMAL;

  IsUnderEnter_b_CMockExpectAndReturn(214, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(215, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(220, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(221, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(223), UNITY_DISPLAY_STYLE_INT);

  IsUnderEnter_b_CMockExpectAndReturn(226, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(227, 0,
 0
 );
  TempMon_Run(0);
  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(229), UNITY_DISPLAY_STYLE_INT);
}

void test_ExtremeLowTemperature(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(237, -100000,
 1
 );

  TempMon_Run(-100000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_UNDER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(241), UNITY_DISPLAY_STYLE_INT);
}

void test_ExtremeHighTemperature(void)
{
  IsUnderEnter_b_CMockExpectAndReturn(249, 100000,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(250, 100000,
 1
 );

  TempMon_Run(100000);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_OVER)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(254), UNITY_DISPLAY_STYLE_INT);
}

void test_ZeroTemperatureInNormalState(void)
{
  Sts_e = TEMPMON_STS_NORMAL;

  IsUnderEnter_b_CMockExpectAndReturn(263, 0,
 0
 );
  IsOverEnter_b_CMockExpectAndReturn(264, 0,
 0
 );

  TempMon_Run(0);

  UnityAssertEqualNumber((UNITY_INT)((TEMPMON_STS_NORMAL)), (UNITY_INT)((Sts_e)), (
 ((void *)0)
 ), (UNITY_UINT)(268), UNITY_DISPLAY_STYLE_INT);
}