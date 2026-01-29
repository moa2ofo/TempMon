#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>

void setUp(void) {
  /* Reset state to NORMAL before each test */
  Sts_e = TEMPMON_STS_NORMAL;
}

void tearDown(void) {}

/* ====== Tests for NORMAL state transitions ====== */

/**
 * @brief Test: Initial state is NORMAL
 */
void test_InitialStateIsNormal(void) { TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e); }

/**
 * @brief Test: NORMAL state remains NORMAL when neither threshold is crossed
 */
void test_NormalStateRemainsNormalWhenNoThresholdCrossed(void) {
  /* Mock: Neither under nor over conditions are met */
  IsUnderEnter_b_ExpectAndReturn(0, false);
  IsOverEnter_b_ExpectAndReturn(0, false);

  TempMon_Run(0);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: NORMAL → UNDER transition when temperature drops below threshold
 */
void test_NormalToUnderTransition(void) {
  /* Mock: Under threshold condition is met */
  IsUnderEnter_b_ExpectAndReturn(-5000, true);

  TempMon_Run(-5000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: NORMAL → OVER transition when temperature rises above threshold
 */
void test_NormalToOverTransition(void) {
  /* Mock: Over threshold condition is met */
  IsUnderEnter_b_ExpectAndReturn(50000, false);
  IsOverEnter_b_ExpectAndReturn(50000, true);

  TempMon_Run(50000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: NORMAL prioritizes UNDER check before OVER check
 * (If both are true, UNDER should be entered)
 */
void test_NormalPrioritizesUnderOverOver(void) {
  /* Mock: Both conditions are met, UNDER should have priority */
  IsUnderEnter_b_ExpectAndReturn(25000, true);

  TempMon_Run(25000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/* ====== Tests for UNDER state transitions ====== */

/**
 * @brief Test: UNDER state remains UNDER when exit condition is not met
 */
void test_UnderStateRemainsUnderWhenNoExit(void) {
  /* Setup: Enter UNDER state first */
  Sts_e = TEMPMON_STS_UNDER;

  /* Mock: Exit condition is not met */
  IsUnderExit_b_ExpectAndReturn(-3000, false);

  TempMon_Run(-3000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: UNDER → NORMAL transition with hysteresis release
 */
void test_UnderToNormalTransitionWithHysteresis(void) {
  /* Setup: Enter UNDER state first */
  Sts_e = TEMPMON_STS_UNDER;

  /* Mock: Exit condition is met (hysteresis threshold exceeded) */
  IsUnderExit_b_ExpectAndReturn(2000, true);

  TempMon_Run(2000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/* ====== Tests for OVER state transitions ====== */

/**
 * @brief Test: OVER state remains OVER when exit condition is not met
 */
void test_OverStateRemainsOverWhenNoExit(void) {
  /* Setup: Enter OVER state first */
  Sts_e = TEMPMON_STS_OVER;

  /* Mock: Exit condition is not met */
  IsOverExit_b_ExpectAndReturn(45000, false);

  TempMon_Run(45000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: OVER → NORMAL transition with hysteresis release
 */
void test_OverToNormalTransitionWithHysteresis(void) {
  /* Setup: Enter OVER state first */
  Sts_e = TEMPMON_STS_OVER;

  /* Mock: Exit condition is met (hysteresis threshold undercut) */
  IsOverExit_b_ExpectAndReturn(30000, true);

  TempMon_Run(30000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/* ====== Tests for state machine cycle ====== */

/**
 * @brief Test: Complete cycle NORMAL → UNDER → NORMAL
 */
void test_CompleteCycleNormalUnderNormal(void) {
  /* Step 1: NORMAL → UNDER */
  IsUnderEnter_b_ExpectAndReturn(-6000, true);
  TempMon_Run(-6000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Step 2: Stay UNDER */
  IsUnderExit_b_ExpectAndReturn(-4000, false);
  TempMon_Run(-4000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Step 3: UNDER → NORMAL */
  IsUnderExit_b_ExpectAndReturn(1000, true);
  TempMon_Run(1000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Complete cycle NORMAL → OVER → NORMAL
 */
void test_CompleteCycleNormalOverNormal(void) {
  /* Step 1: NORMAL → OVER */
  IsUnderEnter_b_ExpectAndReturn(55000, false);
  IsOverEnter_b_ExpectAndReturn(55000, true);
  TempMon_Run(55000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Step 2: Stay OVER */
  IsOverExit_b_ExpectAndReturn(52000, false);
  TempMon_Run(52000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Step 3: OVER → NORMAL */
  IsOverExit_b_ExpectAndReturn(40000, true);
  TempMon_Run(40000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Multiple transitions in sequence
 * NORMAL → UNDER → NORMAL → OVER → NORMAL
 */
void test_MultipleTransitionsSequence(void) {
  /* NORMAL → UNDER */
  IsUnderEnter_b_ExpectAndReturn(-10000, true);
  TempMon_Run(-10000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* UNDER → NORMAL */
  IsUnderExit_b_ExpectAndReturn(5000, true);
  TempMon_Run(5000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* NORMAL → OVER */
  IsUnderEnter_b_ExpectAndReturn(60000, false);
  IsOverEnter_b_ExpectAndReturn(60000, true);
  TempMon_Run(60000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* OVER → NORMAL */
  IsOverExit_b_ExpectAndReturn(35000, true);
  TempMon_Run(35000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/* ====== Tests for edge cases ====== */

/**
 * @brief Test: Multiple consecutive calls with same state
 */
void test_ConsecutiveCallsSameState(void) {
  Sts_e = TEMPMON_STS_NORMAL;

  /* Call 1 */
  IsUnderEnter_b_ExpectAndReturn(0, false);
  IsOverEnter_b_ExpectAndReturn(0, false);
  TempMon_Run(0);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call 2 */
  IsUnderEnter_b_ExpectAndReturn(0, false);
  IsOverEnter_b_ExpectAndReturn(0, false);
  TempMon_Run(0);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call 3 */
  IsUnderEnter_b_ExpectAndReturn(0, false);
  IsOverEnter_b_ExpectAndReturn(0, false);
  TempMon_Run(0);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Extreme low temperature value
 */
void test_ExtremeLowTemperature(void) {
  /* Mock: Extreme low temperature triggers UNDER */
  IsUnderEnter_b_ExpectAndReturn(-100000, true);

  TempMon_Run(-100000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: Extreme high temperature value
 */
void test_ExtremeHighTemperature(void) {
  /* Mock: Extreme high temperature triggers OVER */
  IsUnderEnter_b_ExpectAndReturn(100000, false);
  IsOverEnter_b_ExpectAndReturn(100000, true);

  TempMon_Run(100000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: Zero temperature in NORMAL state
 */
void test_ZeroTemperatureInNormalState(void) {
  Sts_e = TEMPMON_STS_NORMAL;

  IsUnderEnter_b_ExpectAndReturn(0, false);
  IsOverEnter_b_ExpectAndReturn(0, false);

  TempMon_Run(0);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}
