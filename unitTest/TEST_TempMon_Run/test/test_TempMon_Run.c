#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e TempMon_GetSts_stub;
static void TempMon_SetSts(TempMon_sts_e sts);
static TempMon_sts_e TempMon_GetSts_Accessor(void);

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    TempMon_SetSts(TEMPMON_STS_NORMAL);
}

static void TempMon_SetSts(TempMon_sts_e sts)
{
    TempMon_GetSts_stub = sts;
}

static TempMon_sts_e TempMon_GetSts_Accessor(void)
{
    return TempMon_GetSts_stub;
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_just_below_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    UnityAssertEqualInt(TEMPMON_STS_UNDER, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_NORMAL_when_temp_equals_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_NORMAL_when_temp_between_Under_and_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(1500);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_just_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_NORMAL);

    TempMon_Run(2001);

    UnityAssertEqualInt(TEMPMON_STS_OVER, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_OVER_when_temp_equals_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(2000);

    UnityAssertEqualInt(TEMPMON_STS_OVER, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_UNDER_when_temp_below_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1049);

    UnityAssertEqualInt(TEMPMON_STS_UNDER, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_just_above_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1051);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_NORMAL_when_temp_equals_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_UNDER);

    TempMon_Run(1050);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_OVER_when_temp_above_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(1951);

    UnityAssertEqualInt(TEMPMON_STS_OVER, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_just_below_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(1949);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}

void test_TempMon_Run_remains_NORMAL_when_temp_equals_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    TempMon_SetSts(TEMPMON_STS_OVER);

    TempMon_Run(1950);

    UnityAssertEqualInt(TEMPMON_STS_NORMAL, TempMon_GetSts_Accessor(), NULL, 0);
}