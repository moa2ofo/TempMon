#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>

```c
    /* ========================================================================
 * CALLBACKS
 * ======================================================================== */

    static TempMon_sts_e callback_Sts_e;

static bool IsUnderEnter_b_Callback(int32_t temp_mC, int cmock_num_calls) {
  return (temp_mC < g_UnderThreshold_mC_s32);
}

static bool IsUnderExit_b_Callback(int32_t temp_mC, int cmock_num_calls) {
  return (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32));
}

static bool IsOverEnter_b_Callback(int32_t temp_mC, int cmock_num_calls) {
  return (temp_mC > g_OverThreshold_mC_s32);
}

static bool IsOverExit_b_Callback(int32_t temp_mC, int cmock_num_calls) {
  return (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32));
}

static TempMon_sts_e TempMon_GetSts_Callback(int cmock_num_calls) {
  return callback_Sts_e;
}

static void TempMon_GetSts_SetReturnValue(TempMon_sts_e sts) {
  callback_Sts_e = sts;
}

/* ========================================================================
 * SETUP AND TEARDOWN
 * ======================================================================== */

void setUp(void) {
  callback_Sts_e = TEMPMON_STS_NORMAL;
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;
}

void tearDown(void) {
}

/* ========================================================================
 * TEST FUNCTIONS
 * ======================================================================== */

void test_Normal_BelowUnder_TransitionsToUnder(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;

  TempMon_Run(-10001);
}

void test_Normal_EqualUnder_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;

  TempMon_Run(-10000);
}

void test_Normal_JustAboveUnder_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;

  TempMon_Run(-9999);
}

void test_Normal_BetweenThresholds_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(25000);
}

void test_Normal_JustBelowOver_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(84999);
}

void test_Normal_EqualOver_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(85000);
}

void test_Normal_AboveOver_TransitionsToOver(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(85001);
}

void test_Under_BelowRecovery_RemainsUnder(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(-5001);
}

void test_Under_EqualRecovery_RemainsUnder(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(-5000);
}

void test_Under_AboveRecovery_TransitionsToNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(-4999);
}

void test_Over_AboveRecovery_RemainsOver(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(80001);
}

void test_Over_EqualRecovery_RemainsOver(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(80000);
}

void test_Over_BelowRecovery_TransitionsToNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(79999);
}

void test_Normal_INT32MIN_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(INT32_MIN);
}

void test_Normal_INT32MAX_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(INT32_MAX);
}

void test_Under_INT32MAX_PosHyst_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = 1000000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(INT32_MAX);
}

void test_Over_INT32MIN_PosHyst_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = -1000000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(INT32_MIN);
}

void test_Under_ZeroHyst_ImmediateTransition(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = 0;

  TempMon_Run(-9999);
}

void test_Over_ZeroHyst_ImmediateTransition(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 0;

  TempMon_Run(84999);
}

void test_Under_LargeHyst_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -1000000;
  g_Hyst_mC_s32 = 2000000000;

  TempMon_Run(1000000001);
}

void test_Over_LargeHyst_NoOverflow(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 1000000;
  g_Hyst_mC_s32 = 2000000000;

  TempMon_Run(-999999999);
}

void test_Normal_EqualThresholds_BelowBoth_ToUnder(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = 50000;
  g_OverThreshold_mC_s32 = 50000;

  TempMon_Run(49999);
}

void test_Normal_EqualThresholds_AboveBoth_ToOver(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = 50000;
  g_OverThreshold_mC_s32 = 50000;

  TempMon_Run(50001);
}

void test_Normal_UnderGreaterThanOver_Between_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = 60000;
  g_OverThreshold_mC_s32 = 40000;

  TempMon_Run(50000);
}

void test_Under_NegativeHyst_RecoveryCalc(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = -5000;

  TempMon_Run(-15001);
}

void test_Over_NegativeHyst_RecoveryCalc(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = -5000;

  TempMon_Run(90001);
}

void test_Normal_MultipleCalls_StableMid_RemainsNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;

  TempMon_Run(25000);
  TempMon_Run(25000);
  TempMon_Run(25000);
}

void test_Under_MultipleCalls_StableLow_RemainsUnder(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -10000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(-15000);
  TempMon_Run(-15000);
  TempMon_Run(-15000);
}

void test_Over_MultipleCalls_StableHigh_RemainsOver(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;

  TempMon_Run(90000);
  TempMon_Run(90000);
  TempMon_Run(90000);
}

void test_TransitionSequence_NormalUnderNormalOverNormal(void) {
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderEnter_b_Stub(IsUnderEnter_b_Callback);
  IsOverEnter_b_Stub(IsOverEnter_b_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);
  IsOverExit_b_Stub(IsOverExit_b_Callback);

  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  TempMon_Run(-10001);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  TempMon_Run(-4999);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_NORMAL);
  TempMon_Run(85001);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_OVER);
  TempMon_Run(79999);
}
```