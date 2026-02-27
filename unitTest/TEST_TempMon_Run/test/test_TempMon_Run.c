#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>

/* Required callbacks */

/* No callbacks needed for this unit test */

/* Setup and teardown */

void setUp(void) {
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 0;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);
}

void tearDown(void) {
}

/* Test functions */

void test_From_NORMAL_state_temperature_below_under_threshold_transitions_to_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(9999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_equal_to_under_threshold_remains_in_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(10000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_just_above_under_threshold_remains_in_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(10001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_in_mid_range_between_thresholds_remains_in_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(30000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_just_below_over_threshold_remains_in_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(49999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_equal_to_over_threshold_remains_in_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(50000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_above_over_threshold_transitions_to_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(50001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_From_UNDER_state_temperature_below_recovery_threshold_remains_in_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(11999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_UNDER_state_temperature_equal_to_recovery_threshold_remains_in_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(12000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_UNDER_state_temperature_just_above_recovery_threshold_transitions_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(12001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_UNDER_state_temperature_well_above_recovery_threshold_transitions_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(30000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_OVER_state_temperature_above_recovery_threshold_remains_in_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(48001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_From_OVER_state_temperature_equal_to_recovery_threshold_remains_in_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(48000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_From_OVER_state_temperature_just_below_recovery_threshold_transitions_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(47999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_OVER_state_temperature_well_below_recovery_threshold_transitions_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(30000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_with_INT32_MIN_temperature_verify_transition_to_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(INT32_MIN);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_NORMAL_state_with_INT32_MAX_temperature_verify_transition_to_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(INT32_MAX);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_From_UNDER_state_with_INT32_MAX_temperature_verify_transition_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(INT32_MAX);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_OVER_state_with_INT32_MIN_temperature_verify_transition_to_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(INT32_MIN);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_exactly_at_under_threshold_minus_one_transitions_to_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(9999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_NORMAL_state_temperature_exactly_at_over_threshold_plus_one_transitions_to_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(50001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_Hysteresis_value_of_zero_allows_immediate_recovery_from_UNDER_when_temperature_equals_under_threshold(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(10000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_Hysteresis_value_of_zero_allows_immediate_recovery_from_OVER_when_temperature_equals_over_threshold(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 0;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(50000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_Large_positive_hysteresis_value_requires_significant_temperature_increase_to_recover_from_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 20000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(29999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(30001);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_Large_positive_hysteresis_value_requires_significant_temperature_decrease_to_recover_from_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 20000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(30001);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(29999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_From_UNDER_state_temperature_at_exactly_under_threshold_remains_in_UNDER_state_when_hysteresis_is_positive(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(10000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_From_OVER_state_temperature_at_exactly_over_threshold_remains_in_OVER_state_when_hysteresis_is_positive(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(50000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_Multiple_consecutive_calls_in_NORMAL_state_with_stable_mid_range_temperature_maintain_NORMAL_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_Multiple_consecutive_calls_in_UNDER_state_with_stable_low_temperature_maintain_UNDER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_UNDER);

  TempMon_Run(5000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(5000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(5000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(5000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_Multiple_consecutive_calls_in_OVER_state_with_stable_high_temperature_maintain_OVER_state(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_OVER);

  TempMon_Run(60000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(60000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(60000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(60000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_Transition_sequence_NORMAL_to_UNDER_to_NORMAL_to_OVER_to_NORMAL_with_appropriate_temperature_changes(void) {
  g_UnderThreshold_mC_s32 = 10000;
  g_OverThreshold_mC_s32 = 50000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(30000);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());

  TempMon_Run(9999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());

  TempMon_Run(12001);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());

  TempMon_Run(50001);
  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());

  TempMon_Run(47999);
  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_Under_threshold_greater_than_over_threshold_temperature_below_under_threshold_transitions_to_UNDER_from_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 50000;
  g_OverThreshold_mC_s32 = 10000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(49999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_Under_threshold_greater_than_over_threshold_temperature_above_under_threshold_remains_in_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 50000;
  g_OverThreshold_mC_s32 = 10000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(50001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}

void test_Under_threshold_equal_to_over_threshold_temperature_below_threshold_transitions_to_UNDER_from_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 30000;
  g_OverThreshold_mC_s32 = 30000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(29999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_e());
}

void test_Under_threshold_equal_to_over_threshold_temperature_above_threshold_transitions_to_OVER_from_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 30000;
  g_OverThreshold_mC_s32 = 30000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(30001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_e());
}

void test_Under_threshold_equal_to_over_threshold_temperature_exactly_at_threshold_remains_in_NORMAL(void) {
  g_UnderThreshold_mC_s32 = 30000;
  g_OverThreshold_mC_s32 = 30000;
  g_Hyst_mC_s32 = 2000;
  TempMon_SetSts_e(TEMPMON_STS_NORMAL);

  TempMon_Run(30000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_e());
}