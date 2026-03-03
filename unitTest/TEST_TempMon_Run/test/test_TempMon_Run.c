#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e getSts(void);
static void setSts(TempMon_sts_e val);

static TempMon_sts_e s_Sts_e;

static TempMon_sts_e getSts(void)
{
  return s_Sts_e;
}

static void setSts(TempMon_sts_e val)
{
  s_Sts_e = val;
}

void setUp(void)
{
  g_UnderThreshold_mC_s32 = 0;
  g_OverThreshold_mC_s32 = 0;
  g_Hyst_mC_s32 = 0;
  setSts(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_if_temp_just_below_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, getSts());
}

void test_TempMon_Run_remains_NORMAL_if_temp_exactly_at_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(1000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_NORMAL_if_temp_just_above_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(1001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_if_temp_just_above_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(3001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, getSts());
}

void test_TempMon_Run_remains_NORMAL_if_temp_exactly_at_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(3000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_NORMAL_if_temp_just_below_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(2999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_NORMAL_if_temp_between_thresholds(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_NORMAL);

  TempMon_Run(2000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_UNDER_if_temp_just_below_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_UNDER);

  TempMon_Run(1099);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, getSts());
}

void test_TempMon_Run_transitions_UNDER_to_NORMAL_if_temp_exactly_at_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_UNDER);

  TempMon_Run(1100);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_transitions_UNDER_to_NORMAL_if_temp_above_UnderThreshold_plus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_UNDER);

  TempMon_Run(1150);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_OVER_if_temp_just_above_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_OVER);

  TempMon_Run(2901);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, getSts());
}

void test_TempMon_Run_transitions_OVER_to_NORMAL_if_temp_exactly_at_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_OVER);

  TempMon_Run(2900);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_transitions_OVER_to_NORMAL_if_temp_below_OverThreshold_minus_Hyst(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 100;
  setSts(TEMPMON_STS_OVER);

  TempMon_Run(2800);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_remains_OVER_if_temp_just_below_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 0;  // no hysteresis to check border behavior
  setSts(TEMPMON_STS_OVER);

  TempMon_Run(2999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, getSts());
}

void test_TempMon_Run_remains_UNDER_if_temp_equal_to_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 0;  // no hysteresis
  setSts(TEMPMON_STS_UNDER);

  TempMon_Run(1000);

  TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, getSts());
}

void test_TempMon_Run_transitions_UNDER_to_NORMAL_when_hysteresis_zero_and_temp_above_UnderThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 0;  // no hysteresis
  setSts(TEMPMON_STS_UNDER);

  TempMon_Run(1001);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}

void test_TempMon_Run_transitions_OVER_to_NORMAL_when_hysteresis_zero_and_temp_below_OverThreshold(void)
{
  g_UnderThreshold_mC_s32 = 1000;
  g_OverThreshold_mC_s32 = 3000;
  g_Hyst_mC_s32 = 0;  // no hysteresis
  setSts(TEMPMON_STS_OVER);

  TempMon_Run(2999);

  TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, getSts());
}