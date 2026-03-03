#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e Sts_e;

static void set_Sts_e(TempMon_sts_e sts) { Sts_e = sts; }
static TempMon_sts_e get_Sts_e(void) { return Sts_e; }

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    set_Sts_e(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_below_underThreshold(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(9999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, get_Sts_e());
}

void test_TempMon_Run_stays_NORMAL_when_temp_equals_underThreshold(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(10000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_above_underThreshold_but_below_overThreshold(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(10001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_above_overThreshold(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(30001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, get_Sts_e());
}

void test_TempMon_Run_stays_NORMAL_when_temp_equals_overThreshold(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(30000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());
}

void test_TempMon_Run_stays_UNDER_when_temp_below_or_equal_underThreshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_UNDER);

    TempMon_Run(12000); // equals 10000 + 2000

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());

    set_Sts_e(TEMPMON_STS_UNDER);
    TempMon_Run(11999); // just below 12000

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, get_Sts_e());
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_above_underThreshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_UNDER);

    TempMon_Run(12001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());
}

void test_TempMon_Run_stays_OVER_when_temp_above_or_equal_overThreshold_minus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_OVER);

    TempMon_Run(28000); // 30000 - 2000

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());

    set_Sts_e(TEMPMON_STS_OVER);
    TempMon_Run(28001); // just above 28000

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, get_Sts_e());
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_below_overThreshold_minus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 10000;
    g_OverThreshold_mC_s32 = 30000;
    g_Hyst_mC_s32 = 2000;
    set_Sts_e(TEMPMON_STS_OVER);

    TempMon_Run(27999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, get_Sts_e());
}