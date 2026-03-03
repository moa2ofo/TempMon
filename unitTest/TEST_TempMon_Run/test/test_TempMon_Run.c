#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e TempMon_GetSts_State_s;
static void TempMon_SetSts(TempMon_sts_e sts) { TempMon_GetSts_State_s = sts; }
static TempMon_sts_e TempMon_GetSts_Get(void) { return TempMon_GetSts_State_s; }

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_SetSts(TEMPMON_STS_NORMAL);
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_below_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_NORMAL_when_at_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_NORMAL_when_just_above_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(3001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_NORMAL_when_exactly_at_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(3000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_NORMAL_when_just_below_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(2999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_in_NORMAL_when_between_thresholds(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1500);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_in_UNDER_when_below_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1199);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_FROM_UNDER_TO_NORMAL_when_above_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1201);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_in_UNDER_when_exactly_at_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1200);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_in_OVER_when_above_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(2801);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_FROM_OVER_TO_NORMAL_when_below_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(2799);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_in_OVER_when_exactly_at_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;

    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(2800);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}