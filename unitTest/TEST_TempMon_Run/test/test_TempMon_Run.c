#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e TempMon_sts_e_Setter;
static TempMon_sts_e TempMon_sts_e_Getter;
static int32_t g_UnderThreshold_mC_s32_Setter;
static int32_t g_OverThreshold_mC_s32_Setter;
static int32_t g_Hyst_mC_s32_Setter;

static void TempMon_sts_e_Set(TempMon_sts_e sts)
{
    TempMon_sts_e_Setter = sts;
}

static TempMon_sts_e TempMon_sts_e_Get(void)
{
    return TempMon_sts_e_Setter;
}

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_sts_e_Set(0);
}

void test_TempMon_Run_TransitionsFromNormalToUnderWhenTempJustBelowUnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_Get());
}

void test_TempMon_Run_TransitionsFromNormalToUnderWhenTempExactlyAtUnderThresholdMinusOne(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 0;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysNormalWhenTempExactlyAtUnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_Get());
}

void test_TempMon_Run_TransitionsFromNormalToOverWhenTempJustAboveOverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(3001);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysNormalWhenTempExactlyAtOverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(3000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysNormalWhenTempBetweenThresholds(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 200;
    TempMon_sts_e_Set(TEMPMON_STS_NORMAL);

    TempMon_Run(2000);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_Get());
}

void test_TempMon_Run_TransitionsFromUnderToNormalWhenTempJustAboveUnderThresholdPlusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_UNDER);

    TempMon_Run(1101);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysUnderWhenTempExactlyAtUnderThresholdPlusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_UNDER);

    TempMon_Run(1100);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysUnderWhenTempJustBelowUnderThresholdPlusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_UNDER);

    TempMon_Run(1099);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_UNDER, TempMon_sts_e_Get());
}

void test_TempMon_Run_TransitionsFromOverToNormalWhenTempJustBelowOverThresholdMinusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_OVER);

    TempMon_Run(2899);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_NORMAL, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysOverWhenTempExactlyAtOverThresholdMinusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_OVER);

    TempMon_Run(2900);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_Get());
}

void test_TempMon_Run_StaysOverWhenTempJustAboveOverThresholdMinusHyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 3000;
    g_Hyst_mC_s32 = 100;
    TempMon_sts_e_Set(TEMPMON_STS_OVER);

    TempMon_Run(2901);

    TEST_ASSERT_EQUAL_INT(TEMPMON_STS_OVER, TempMon_sts_e_Get());
}