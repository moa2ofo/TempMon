#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>

/* Extern variables for accessing global state and thresholds */
extern int32_t g_UnderThreshold_mC_s32;
extern int32_t g_OverThreshold_mC_s32;
extern int32_t g_Hyst_mC_s32;
extern TempMon_sts_e Sts_e;

void setUp(void) {
  /* Reset state to NORMAL before each test */
  Sts_e = TEMPMON_STS_NORMAL;
  /* Reset thresholds to default values */
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 2000;
}

void tearDown(void) {}

/* ===== Test cases for NORMAL state transitions ===== */

/**
 * @brief Test: In NORMAL state, temperature above over-threshold transitions to
 * OVER.
 */
void test_TempMon_Run_NORMAL_to_OVER_TransitionAboveThreshold(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp > over-threshold */
  TempMon_Run(90000); /* 90.000°C > 85.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature below under-threshold transitions
 * to UNDER.
 */
void test_TempMon_Run_NORMAL_to_UNDER_TransitionBelowThreshold(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp < under-threshold */
  TempMon_Run(-5000); /* -5.000°C < 0.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature within thresholds stays NORMAL.
 */
void test_TempMon_Run_NORMAL_StaysNormalWithinThresholds(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp within normal range */
  TempMon_Run(25000); /* 25.000°C is between 0°C and 85°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature at over-threshold boundary stays
 * NORMAL.
 */
void test_TempMon_Run_NORMAL_AtOverThresholdBoundaryStaysNormal(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp = over-threshold (should NOT transition yet) */
  TempMon_Run(85000); /* 85.000°C = 85.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature just above over-threshold
 * transitions to OVER.
 */
void test_TempMon_Run_NORMAL_JustAboveOverThresholdTransitionsToOVER(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp just above over-threshold */
  TempMon_Run(85001); /* 85.001°C > 85.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature at under-threshold boundary stays
 * NORMAL.
 */
void test_TempMon_Run_NORMAL_AtUnderThresholdBoundaryStaysNormal(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp = under-threshold (should NOT transition yet) */
  TempMon_Run(0); /* 0.000°C = 0.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: In NORMAL state, temperature just below under-threshold
 * transitions to UNDER.
 */
void test_TempMon_Run_NORMAL_JustBelowUnderThresholdTransitionsToUNDER(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Call with temp just below under-threshold */
  TempMon_Run(-1); /* -0.001°C < 0.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/* ===== Test cases for UNDER state transitions ===== */

/**
 * @brief Test: In UNDER state, temperature below under-threshold stays UNDER.
 */
void test_TempMon_Run_UNDER_StaysUnderBelowThreshold(void) {
  Sts_e = TEMPMON_STS_UNDER;

  /* Call with temp below under-threshold */
  TempMon_Run(-10000); /* -10.000°C < 0.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: In UNDER state, temperature above hysteresis threshold
 * transitions to NORMAL.
 */
void test_TempMon_Run_UNDER_to_NORMAL_TransitionAboveHysteresisThreshold(void) {
  Sts_e = TEMPMON_STS_UNDER;

  /* Call with temp > (under-threshold + hysteresis) */
  /* (0 + 2000) = 2000 */
  TempMon_Run(2001); /* 2.001°C > 2.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: In UNDER state, temperature at hysteresis boundary stays UNDER.
 */
void test_TempMon_Run_UNDER_AtHysteresisThresholdStaysUnder(void) {
  Sts_e = TEMPMON_STS_UNDER;

  /* Call with temp = (under-threshold + hysteresis) */
  /* (0 + 2000) = 2000 */
  TempMon_Run(2000); /* 2.000°C = 2.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: In UNDER state, temperature between under and hysteresis stays
 * UNDER.
 */
void test_TempMon_Run_UNDER_StaysUnderBetweenUnderAndHysteresis(void) {
  Sts_e = TEMPMON_STS_UNDER;

  /* Call with temp between under-threshold and (under-threshold + hysteresis)
   */
  TempMon_Run(1000); /* 1.000°C is between 0°C and 2.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/* ===== Test cases for OVER state transitions ===== */

/**
 * @brief Test: In OVER state, temperature above over-threshold stays OVER.
 */
void test_TempMon_Run_OVER_StaysOverAboveThreshold(void) {
  Sts_e = TEMPMON_STS_OVER;

  /* Call with temp above over-threshold */
  TempMon_Run(95000); /* 95.000°C > 85.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: In OVER state, temperature below hysteresis threshold
 * transitions to NORMAL.
 */
void test_TempMon_Run_OVER_to_NORMAL_TransitionBelowHysteresisThreshold(void) {
  Sts_e = TEMPMON_STS_OVER;

  /* Call with temp < (over-threshold - hysteresis) */
  /* (85000 - 2000) = 83000 */
  TempMon_Run(82999); /* 82.999°C < 83.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: In OVER state, temperature at hysteresis boundary stays OVER.
 */
void test_TempMon_Run_OVER_AtHysteresisThresholdStaysOver(void) {
  Sts_e = TEMPMON_STS_OVER;

  /* Call with temp = (over-threshold - hysteresis) */
  /* (85000 - 2000) = 83000 */
  TempMon_Run(83000); /* 83.000°C = 83.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/**
 * @brief Test: In OVER state, temperature between over and hysteresis stays
 * OVER.
 */
void test_TempMon_Run_OVER_StaysOverBetweenOverAndHysteresis(void) {
  Sts_e = TEMPMON_STS_OVER;

  /* Call with temp between (over-threshold - hysteresis) and over-threshold */
  TempMon_Run(84000); /* 84.000°C is between 83.000°C and 85.000°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/* ===== Test cases for hysteresis behavior (no oscillation) ===== */

/**
 * @brief Test: Hysteresis prevents oscillation near UNDER threshold.
 */
void test_TempMon_Run_HysteresisPreventOscillationAtUnderThreshold(void) {
  Sts_e = TEMPMON_STS_UNDER;

  /* Temperature just below under-threshold should NOT exit UNDER state */
  TempMon_Run(500); /* 0.5°C is below hysteresis threshold of 2.0°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Even closer to under-threshold */
  TempMon_Run(1500); /* 1.5°C is still below hysteresis threshold of 2.0°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);
}

/**
 * @brief Test: Hysteresis prevents oscillation near OVER threshold.
 */
void test_TempMon_Run_HysteresisPreventOscillationAtOverThreshold(void) {
  Sts_e = TEMPMON_STS_OVER;

  /* Temperature just above over-threshold should NOT exit OVER state */
  TempMon_Run(84500); /* 84.5°C is above hysteresis threshold of 83.0°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Even closer to over-threshold */
  TempMon_Run(
      84999); /* 84.999°C is still above hysteresis threshold of 83.0°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}

/* ===== Test cases for edge cases and boundary conditions ===== */

/**
 * @brief Test: Sequential state machine transitions NORMAL -> OVER -> NORMAL.
 */
void test_TempMon_Run_SequentialTransitions_NORMAL_OVER_NORMAL(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Transition to OVER */
  TempMon_Run(86000); /* 86.000°C > 85.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Stay in OVER */
  TempMon_Run(84000); /* 84.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Transition back to NORMAL */
  TempMon_Run(82999); /* 82.999°C < 83.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Sequential state machine transitions NORMAL -> UNDER -> NORMAL.
 */
void test_TempMon_Run_SequentialTransitions_NORMAL_UNDER_NORMAL(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Transition to UNDER */
  TempMon_Run(-1000); /* -1.000°C < 0.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Stay in UNDER */
  TempMon_Run(1000); /* 1.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Transition back to NORMAL */
  TempMon_Run(2001); /* 2.001°C > 2.000°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Multiple cycles between NORMAL and OVER states.
 */
void test_TempMon_Run_MultipleCyclesNormalOver(void) {
  /* Cycle 1 */
  TempMon_Run(90000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
  TempMon_Run(82999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Cycle 2 */
  TempMon_Run(86000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
  TempMon_Run(82999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Custom threshold and hysteresis values.
 */
void test_TempMon_Run_CustomThresholdAndHysteresis(void) {
  /* Change configuration */
  g_UnderThreshold_mC_s32 = 10000; /* 10°C */
  g_OverThreshold_mC_s32 = 30000;  /* 30°C */
  g_Hyst_mC_s32 = 5000;            /* 5°C */

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Transition to OVER */
  TempMon_Run(35000); /* 35°C > 30°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* At hysteresis boundary should stay OVER */
  TempMon_Run(25000); /* 25°C = 30°C - 5°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);

  /* Below hysteresis should return to NORMAL */
  TempMon_Run(24999); /* 24.999°C < 25°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);
}

/**
 * @brief Test: Extreme temperature values.
 */
void test_TempMon_Run_ExtremeTemperatureValues(void) {
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, Sts_e);

  /* Very low temperature */
  TempMon_Run(-100000); /* -100°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, Sts_e);

  /* Return to NORMAL */
  Sts_e = TEMPMON_STS_NORMAL;

  /* Very high temperature */
  TempMon_Run(150000); /* 150°C */
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, Sts_e);
}
