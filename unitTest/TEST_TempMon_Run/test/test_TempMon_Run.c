#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static void reset_globals_and_statics(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_SetSts_e(TEMPMON_STS_NORMAL);
}

void setUp(void)
{
    reset_globals_and_statics();
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_just_below_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_exactly_at_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_just_above_UnderThreshold_below_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_just_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(5001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_exactly_at_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(5000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_just_below_OverThreshold_above_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(4999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_just_above_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1101);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_UNDER_when_temp_exactly_at_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1100);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_UNDER_when_temp_just_below_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1099);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts());
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_just_below_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(4899);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_OVER_when_temp_exactly_at_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(4900);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts());
}

void test_TempMon_Run_stays_in_OVER_when_temp_just_above_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(4901);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts());
}