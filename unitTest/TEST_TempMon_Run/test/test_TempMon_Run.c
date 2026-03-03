#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e TempMon_sts_e_get(void);
static void TempMon_sts_e_set(TempMon_sts_e val);

static TempMon_sts_e TempMon_sts_e_cur;

static TempMon_sts_e TempMon_sts_e_get(void)
{
    return TempMon_sts_e_cur;
}

static void TempMon_sts_e_set(TempMon_sts_e val)
{
    TempMon_sts_e_cur = val;
}

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_transitions_to_UNDER_when_temp_just_below_under_threshold_in_NORMAL_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_under_threshold_in_NORMAL_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_above_under_threshold_and_below_over_threshold_in_NORMAL_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);

    TempMon_Run(1500);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_transitions_to_OVER_when_temp_just_above_over_threshold_in_NORMAL_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);

    TempMon_Run(3001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_over_threshold_in_NORMAL_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_NORMAL);

    TempMon_Run(3000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_OVER_when_temp_just_above_over_threshold_in_OVER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_OVER);

    TempMon_Run(3001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_get());
}

void test_TempMon_Run_transitions_to_NORMAL_when_temp_just_below_over_threshold_minus_hyst_in_OVER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_OVER);

    TempMon_Run(2950);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_OVER_when_temp_exactly_at_over_threshold_minus_hyst_in_OVER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_OVER);

    TempMon_Run(2950);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_OVER_when_temp_just_above_over_threshold_minus_hyst_in_OVER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_OVER);

    TempMon_Run(2951);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_UNDER_when_temp_just_below_under_threshold_in_UNDER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_UNDER);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_UNDER_when_temp_exactly_at_under_threshold_in_UNDER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_UNDER);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_get());
}

void test_TempMon_Run_transitions_to_NORMAL_when_temp_just_above_under_threshold_plus_hyst_in_UNDER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_UNDER);

    TempMon_Run(1051);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_UNDER_when_temp_just_below_under_threshold_plus_hyst_in_UNDER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_UNDER);

    TempMon_Run(1049);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_get());
}

void test_TempMon_Run_stays_UNDER_when_temp_exactly_at_under_threshold_plus_hyst_in_UNDER_state(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    TempMon_sts_e_set(TEMPMON_STS_UNDER);

    TempMon_Run(1050);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_get());
}