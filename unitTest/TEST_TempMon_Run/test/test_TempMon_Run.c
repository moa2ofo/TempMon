#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>

void resetVar(TempMon_sts_e l_Sts_e, int32_t l_UnderThreshold_mC_s32, int32_t l_OverThreshold_mC_s32, int32_t l_Hyst_mC_s32) {
  l_Sts_e = TEMPMON_STS_NORMAL;
  l_UnderThreshold_mC_s32 = 0;
  l_OverThreshold_mC_s32 = 0;
  l_Hyst_mC_s32 = 0;
}

/**
 * @brief Assert that global variables match expected values
 */
void assertVar(TempMon_sts_e expected_sts, int32_t expected_under, int32_t expected_over, int32_t expected_hyst) {
  TEST_ASSERT_EQUAL_INT32(expected_sts, Sts_e);
  TEST_ASSERT_EQUAL_INT32(expected_under, g_UnderThreshold_mC_s32);
  TEST_ASSERT_EQUAL_INT32(expected_over, g_OverThreshold_mC_s32);
  TEST_ASSERT_EQUAL_INT32(expected_hyst, g_Hyst_mC_s32);
}

void setUp(void) {
  /* Reset state to NORMAL before each test */
  resetVar(0, 0, 0, 0);
}

void tearDown(void) {}

/* ====== Tests for NORMAL state transitions ====== */

/**
 * @brief Test NORMAL state remains NORMAL with temp in safe range
 */
void test_NORMAL_state_remains_NORMAL_when_temp_in_range(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Temperature in safe range (between under and over thresholds) */
  TempMon_Run(25000); /* 25°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test NORMAL state transitions to UNDER when temp goes below threshold
 */
void test_NORMAL_to_UNDER_transition(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Temperature below under threshold */
  TempMon_Run(3000); /* 3°C */

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

/**
 * @brief Test NORMAL state transitions to OVER when temp goes above threshold
 */
void test_NORMAL_to_OVER_transition(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Temperature above over threshold */
  TempMon_Run(45000); /* 45°C */

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

/**
 * @brief Test NORMAL state with temp exactly at under threshold (edge case)
 */
void test_NORMAL_state_at_under_threshold_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Temperature exactly at under threshold - should NOT transition */
  TempMon_Run(5000); /* 5°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test NORMAL state with temp exactly at over threshold (edge case)
 */
void test_NORMAL_state_at_over_threshold_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Temperature exactly at over threshold - should NOT transition */
  TempMon_Run(40000); /* 40°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/* ====== Tests for UNDER state transitions ====== */

/**
 * @brief Test UNDER state remains UNDER when temp still below hysteresis exit point
 */
void test_UNDER_state_remains_UNDER_when_temp_below_hysteresis(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Temperature below exit threshold: UnderThreshold + Hysteresis = 5000 + 2000 = 7000 */
  TempMon_Run(6000); /* 6°C */

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

/**
 * @brief Test UNDER state transitions back to NORMAL when temp exceeds hysteresis
 */
void test_UNDER_to_NORMAL_transition_with_hysteresis(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Temperature above exit threshold: UnderThreshold + Hysteresis = 5000 + 2000 = 7000 */
  TempMon_Run(7500); /* 7.5°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test UNDER state at hysteresis boundary (edge case)
 */
void test_UNDER_state_at_hysteresis_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Temperature exactly at exit threshold: UnderThreshold + Hysteresis = 7000 */
  /* Should NOT transition (requires > not >=) */
  TempMon_Run(7000); /* 7°C */

  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);
}

/**
 * @brief Test UNDER state just above hysteresis boundary (edge case)
 */
void test_UNDER_state_just_above_hysteresis_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Temperature just above exit threshold */
  TempMon_Run(7001); /* 7.001°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/* ====== Tests for OVER state transitions ====== */

/**
 * @brief Test OVER state remains OVER when temp still above hysteresis exit point
 */
void test_OVER_state_remains_OVER_when_temp_above_hysteresis(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_OVER;

  /* Temperature above exit threshold: OverThreshold - Hysteresis = 40000 - 2000 = 38000 */
  TempMon_Run(39000); /* 39°C */

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

/**
 * @brief Test OVER state transitions back to NORMAL when temp drops below hysteresis
 */
void test_OVER_to_NORMAL_transition_with_hysteresis(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_OVER;

  /* Temperature below exit threshold: OverThreshold - Hysteresis = 40000 - 2000 = 38000 */
  TempMon_Run(37000); /* 37°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test OVER state at hysteresis boundary (edge case)
 */
void test_OVER_state_at_hysteresis_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_OVER;

  /* Temperature exactly at exit threshold: OverThreshold - Hysteresis = 38000 */
  /* Should NOT transition (requires < not <=) */
  TempMon_Run(38000); /* 38°C */

  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);
}

/**
 * @brief Test OVER state just below hysteresis boundary (edge case)
 */
void test_OVER_state_just_below_hysteresis_boundary(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_OVER;

  /* Temperature just below exit threshold */
  TempMon_Run(37999); /* 37.999°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/* ====== Tests for state machine cycling and edge cases ====== */

/**
 * @brief Test cycling through states: NORMAL -> UNDER -> NORMAL
 */
void test_cycle_NORMAL_to_UNDER_back_to_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Go UNDER */
  TempMon_Run(3000); /* 3°C */
  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 2000);

  /* Return to NORMAL */
  TempMon_Run(8000); /* 8°C */
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test cycling through states: NORMAL -> OVER -> NORMAL
 */
void test_cycle_NORMAL_to_OVER_back_to_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 2000;           /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Go OVER */
  TempMon_Run(45000); /* 45°C */
  assertVar(TEMPMON_STS_OVER, 5000, 40000, 2000);

  /* Return to NORMAL */
  TempMon_Run(36000); /* 36°C */
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 2000);
}

/**
 * @brief Test with zero hysteresis
 */
void test_zero_hysteresis_UNDER_to_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 0;              /* No hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Just above threshold should return to NORMAL */
  TempMon_Run(5001); /* 5.001°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 0);
}

/**
 * @brief Test with zero hysteresis OVER to NORMAL
 */
void test_zero_hysteresis_OVER_to_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 0;              /* No hysteresis */

  Sts_e = TEMPMON_STS_OVER;

  /* Just below threshold should return to NORMAL */
  TempMon_Run(39999); /* 39.999°C */

  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 0);
}

/**
 * @brief Test with large hysteresis
 */
void test_large_hysteresis_UNDER_to_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 5000; /* 5°C */
  g_OverThreshold_mC_s32 = 40000; /* 40°C */
  g_Hyst_mC_s32 = 5000;           /* 5°C hysteresis */

  Sts_e = TEMPMON_STS_UNDER;

  /* Exit threshold: 5000 + 5000 = 10000 */
  TempMon_Run(9999); /* Still below exit threshold */
  assertVar(TEMPMON_STS_UNDER, 5000, 40000, 5000);

  TempMon_Run(10001); /* Above exit threshold */
  assertVar(TEMPMON_STS_NORMAL, 5000, 40000, 5000);
}

/**
 * @brief Test with negative temperatures
 */
void test_negative_temperatures(void) {
  g_UnderThreshold_mC_s32 = -10000; /* -10°C */
  g_OverThreshold_mC_s32 = 50000;   /* 50°C */
  g_Hyst_mC_s32 = 2000;             /* 2°C hysteresis */

  Sts_e = TEMPMON_STS_NORMAL;

  /* Test with negative temperature */
  TempMon_Run(-15000); /* -15°C - below threshold */
  assertVar(TEMPMON_STS_UNDER, -10000, 50000, 2000);
}
