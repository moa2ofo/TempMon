#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e TempMon_GetSts_State;
static void TempMon_SetSts(TempMon_sts_e sts) { TempMon_GetSts_State = sts; }
static TempMon_sts_e TempMon_GetSts_Get(void) { return TempMon_GetSts_State; }

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_SetSts(TEMPMON_STS_NORMAL);
}

void TempMon_Run(int32_t temp_mC)
{
    TempMon_sts_e Sts_e = TempMon_GetSts_Get();

    if (Sts_e == TEMPMON_STS_NORMAL)
    {
        if (temp_mC < g_UnderThreshold_mC_s32)
        {
            Sts_e = TEMPMON_STS_UNDER;
        }
        else if (temp_mC > g_OverThreshold_mC_s32)
        {
            Sts_e = TEMPMON_STS_OVER;
        }
    }
    else if (Sts_e == TEMPMON_STS_UNDER)
    {
        if (temp_mC > g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)
        {
            Sts_e = TEMPMON_STS_NORMAL;
        }
    }
    else // TEMPMON_STS_OVER
    {
        if (temp_mC < g_OverThreshold_mC_s32 - g_Hyst_mC_s32)
        {
            Sts_e = TEMPMON_STS_NORMAL;
        }
    }

    TempMon_SetSts(Sts_e);
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_just_below_under_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_under_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_above_under_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_just_above_over_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(5001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_over_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(5000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_below_over_threshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(4999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_just_above_threshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1201);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_UNDER_when_temp_exactly_at_threshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1200);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_UNDER_when_temp_just_below_threshold_plus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1199);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_GetSts_Get());
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_just_below_threshold_minus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(4799);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_OVER_when_temp_exactly_at_threshold_minus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(4800);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_GetSts_Get());
}

void test_TempMon_Run_stays_OVER_when_temp_just_above_threshold_minus_hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 5000;
    g_Hyst_mC_s32 = 200;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(4801);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_GetSts_Get());
}