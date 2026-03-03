#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e Sts_e_static;

static void SetSts_e(TempMon_sts_e sts) {
    Sts_e_static = sts;
}

static TempMon_sts_e GetSts_e(void) {
    return Sts_e_static;
}

void setUp(void) {
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    SetSts_e(TEMPMON_STS_NORMAL);
}

void TempMon_Run(int32_t temp_mC);

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_below_UnderThreshold(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, GetSts_e());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_at_UnderThreshold(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, GetSts_e());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_just_above_UnderThreshold_and_below_OverThreshold(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, GetSts_e());
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_above_OverThreshold(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(3001);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, GetSts_e());
}

void test_TempMon_Run_stays_in_NORMAL_when_temp_at_OverThreshold(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(3000);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, GetSts_e());
}

void test_TempMon_Run_stays_in_UNDER_when_temp_below_UnderThreshold_plus_Hyst(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1000 + 50 - 1);

    TEST_ASSERT_EQUAL(TEMPMON_STS_UNDER, GetSts_e());
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_above_UnderThreshold_plus_Hyst(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1000 + 50 + 1);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, GetSts_e());
}

void test_TempMon_Run_stays_in_OVER_when_temp_above_OverThreshold_minus_Hyst(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(3000 - 50 + 1);

    TEST_ASSERT_EQUAL(TEMPMON_STS_OVER, GetSts_e());
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_below_OverThreshold_minus_Hyst(void) {
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(3000 - 50 - 1);

    TEST_ASSERT_EQUAL(TEMPMON_STS_NORMAL, GetSts_e());
}