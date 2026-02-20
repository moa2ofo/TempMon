#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_Init(0);
}

void test_TempMon_Init_SetsInitialThresholdsAndHysteresis(void)
{
    int32_t initial_temp = 25000;

    TempMon_Init(initial_temp);

    TEST_ASSERT_EQUAL_INT32(initial_temp - g_Hyst_mC_s32, g_UnderThreshold_mC_s32);
    TEST_ASSERT_EQUAL_INT32(initial_temp + g_Hyst_mC_s32, g_OverThreshold_mC_s32);
}

void test_TempMon_GetSts_ReturnsNormal_WhenTempWithinThresholds(void)
{
    int32_t temp_in_range = 5000;
    TempMon_Init(temp_in_range);

    g_UnderThreshold_mC_s32 = 4000;
    g_OverThreshold_mC_s32 = 6000;

    TempMon_Init(temp_in_range);

    int32_t test_temp = 5000;

    TempMon_Run(test_temp);

    TempMon_sts_e status = TempMon_GetSts();

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, status);
}

void test_TempMon_GetSts_ReturnsUnder_WhenTempBelowUnderThreshold(void)
{
    int32_t initial_temp = 20000;
    TempMon_Init(initial_temp);

    g_UnderThreshold_mC_s32 = 19000;
    g_OverThreshold_mC_s32 = 21000;
    g_Hyst_mC_s32 = 1000;

    int32_t temp_just_below = g_UnderThreshold_mC_s32 - 1;

    TempMon_Run(temp_just_below);

    TempMon_sts_e status = TempMon_GetSts();

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, status);
    TEST_ASSERT_TRUE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_FALSE(TempMon_IsOverAlv_b());
}

void test_TempMon_GetSts_ReturnsUnder_WhenTempExactlyAtUnderThreshold(void)
{
    int32_t initial_temp = 20000;
    TempMon_Init(initial_temp);

    g_UnderThreshold_mC_s32 = 19000;
    g_OverThreshold_mC_s32 = 21000;
    g_Hyst_mC_s32 = 1000;

    int32_t temp_at_under = g_UnderThreshold_mC_s32;

    TempMon_Run(temp_at_under);

    TempMon_sts_e status = TempMon_GetSts();

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, status);
    TEST_ASSERT_FALSE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_FALSE(TempMon_IsOverAlv_b());
}

void test_TempMon_GetSts_ReturnsOver_WhenTempAboveOverThreshold(void)
{
    int32_t initial_temp = 20000;
    TempMon_Init(initial_temp);

    g_UnderThreshold_mC_s32 = 19000;
    g_OverThreshold_mC_s32 = 21000;
    g_Hyst_mC_s32 = 1000;

    int32_t temp_just_above = g_OverThreshold_mC_s32 + 1;

    TempMon_Run(temp_just_above);

    TempMon_sts_e status = TempMon_GetSts();

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, status);
    TEST_ASSERT_FALSE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_TRUE(TempMon_IsOverAlv_b());
}

void test_TempMon_GetSts_ReturnsOver_WhenTempExactlyAtOverThreshold(void)
{
    int32_t initial_temp = 20000;
    TempMon_Init(initial_temp);

    g_UnderThreshold_mC_s32 = 19000;
    g_OverThreshold_mC_s32 = 21000;
    g_Hyst_mC_s32 = 1000;

    int32_t temp_at_over = g_OverThreshold_mC_s32;

    TempMon_Run(temp_at_over);

    TempMon_sts_e status = TempMon_GetSts();

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, status);
    TEST_ASSERT_FALSE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_FALSE(TempMon_IsOverAlv_b());
}

void test_TempMon_Run_AdjustsThresholds_WhenCrossingUnderThreshold_WithHysteresis(void)
{
    int32_t temp_normal = 20000;
    g_Hyst_mC_s32 = 1000;
    TempMon_Init(temp_normal);

    int32_t temp_below = g_UnderThreshold_mC_s32 - 1;

    TempMon_Run(temp_below);

    TEST_ASSERT_TRUE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_FALSE(TempMon_IsOverAlv_b());

    int32_t expected_under_threshold = temp_below - g_Hyst_mC_s32;
    int32_t expected_over_threshold = temp_below + g_Hyst_mC_s32;

    TEST_ASSERT_EQUAL_INT32(expected_under_threshold, g_UnderThreshold_mC_s32);
    TEST_ASSERT_EQUAL_INT32(expected_over_threshold, g_OverThreshold_mC_s32);
}

void test_TempMon_Run_AdjustsThresholds_WhenCrossingOverThreshold_WithHysteresis(void)
{
    int32_t temp_normal = 20000;
    g_Hyst_mC_s32 = 1000;
    TempMon_Init(temp_normal);

    int32_t temp_above = g_OverThreshold_mC_s32 + 1;

    TempMon_Run(temp_above);

    TEST_ASSERT_FALSE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_TRUE(TempMon_IsOverAlv_b());

    int32_t expected_under_threshold = temp_above - g_Hyst_mC_s32;
    int32_t expected_over_threshold = temp_above + g_Hyst_mC_s32;

    TEST_ASSERT_EQUAL_INT32(expected_under_threshold, g_UnderThreshold_mC_s32);
    TEST_ASSERT_EQUAL_INT32(expected_over_threshold, g_OverThreshold_mC_s32);
}

void test_TempMon_Run_DoesNotAdjustThresholds_WhenTempInNormalRange(void)
{
    g_Hyst_mC_s32 = 1000;
    int32_t initial_temp = 20000;
    TempMon_Init(initial_temp);

    int32_t temp_normal = (g_UnderThreshold_mC_s32 + g_OverThreshold_mC_s32) / 2;

    int32_t old_under = g_UnderThreshold_mC_s32;
    int32_t old_over = g_OverThreshold_mC_s32;

    TempMon_Run(temp_normal);

    TEST_ASSERT_EQUAL_INT32(old_under, g_UnderThreshold_mC_s32);
    TEST_ASSERT_EQUAL_INT32(old_over, g_OverThreshold_mC_s32);
    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_GetSts());
    TEST_ASSERT_FALSE(TempMon_IsUnderAlv_b());
    TEST_ASSERT_FALSE(TempMon_IsOverAlv_b());
}