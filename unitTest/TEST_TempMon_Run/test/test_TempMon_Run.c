#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e Sts_e;

static TempMon_sts_e TempMon_GetSts_static(void)
{
    return Sts_e;
}

static void TempMon_SetSts_static(TempMon_sts_e sts)
{
    Sts_e = sts;
}

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_SetSts_static(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_below_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_NORMAL_when_temp_at_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_static());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_NORMAL);

    TempMon_Run(2001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_NORMAL_when_temp_at_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_NORMAL);

    TempMon_Run(2000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_NORMAL_when_temp_between_thresholds(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;
    TempMon_SetSts_static(TEMPMON_STS_NORMAL);

    TempMon_Run(1500);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_static());
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_above_UnderThreshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_UNDER);

    TempMon_Run(1101);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_UNDER_when_temp_at_UnderThreshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_UNDER);

    TempMon_Run(1100);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_UNDER_when_temp_just_below_UnderThreshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_UNDER);

    TempMon_Run(1099);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, TempMon_GetSts_static());
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_below_OverThreshold_minus_hyst(void)
{
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_OVER);

    TempMon_Run(1899);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_OVER_when_temp_at_OverThreshold_minus_hyst(void)
{
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_OVER);

    TempMon_Run(1900);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_static());
}

void test_TempMon_Run_remains_OVER_when_temp_just_above_OverThreshold_minus_hyst(void)
{
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 100;

    TempMon_SetSts_static(TEMPMON_STS_OVER);

    TempMon_Run(1901);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, TempMon_GetSts_static());
}