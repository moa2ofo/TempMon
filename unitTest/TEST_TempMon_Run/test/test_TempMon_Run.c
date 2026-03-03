#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMon_sts_e Sts_e;

static void SetSts_e(TempMon_sts_e sts)
{
    Sts_e = sts;
}
static TempMon_sts_e GetSts_e(void)
{
    return Sts_e;
}

void setUp(void)
{
    g_UnderThreshold_mC_s32 = 0;
    g_OverThreshold_mC_s32 = 0;
    g_Hyst_mC_s32 = 0;
    SetSts_e(TEMPMON_STS_NORMAL);
}

static void TempMon_Run(int32_t temp_mC)
{
    if(GetSts_e() == TEMPMON_STS_NORMAL)
    {
        if(temp_mC < g_UnderThreshold_mC_s32)
        {
            SetSts_e(TEMPMON_STS_UNDER);
        }
        else
        {
            if(temp_mC > g_OverThreshold_mC_s32)
            {
                SetSts_e(TEMPMON_STS_OVER);
            }
        }
    }
    else if(GetSts_e() == TEMPMON_STS_UNDER)
    {
        if(temp_mC > g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)
        {
            SetSts_e(TEMPMON_STS_NORMAL);
        }
    }
    else
    {
        if(temp_mC < g_OverThreshold_mC_s32 - g_Hyst_mC_s32)
        {
            SetSts_e(TEMPMON_STS_NORMAL);
        }
    }
}

void test_TempMon_Run_transitions_from_NORMAL_to_UNDER_when_temp_just_below_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(999);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_UNDER), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)91, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_UnderThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1000);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)101, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_above_UnderThreshold_and_below_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1500);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)111, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_NORMAL_to_OVER_when_temp_just_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(2001);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_OVER), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)121, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_NORMAL_when_temp_exactly_at_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(2000);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)131, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_OVER_when_temp_just_above_OverThreshold(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(2025);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_OVER), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)141, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_OVER_to_NORMAL_when_temp_just_below_OverThreshold_minus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_OVER);

    TempMon_Run(1949);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)151, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_UNDER_when_temp_just_below_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1049);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_UNDER), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)161, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_transitions_from_UNDER_to_NORMAL_when_temp_just_above_UnderThreshold_plus_Hyst(void)
{
    g_UnderThreshold_mC_s32 = 1000;
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    SetSts_e(TEMPMON_STS_UNDER);

    TempMon_Run(1051);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)171, UNITY_DISPLAY_STYLE_INT);
}

void test_TempMon_Run_stays_NORMAL_when_temp_just_above_OverThreshold_minus_Hyst(void)
{
    g_OverThreshold_mC_s32 = 2000;
    g_Hyst_mC_s32 = 50;
    g_UnderThreshold_mC_s32 = 1000;
    SetSts_e(TEMPMON_STS_NORMAL);

    TempMon_Run(1951);

    UnityAssertEqualNumber((UNITY_INT)(TEMPMON_STS_NORMAL), (UNITY_INT)(GetSts_e()), ((void *)0), (UNITY_UINT)181, UNITY_DISPLAY_STYLE_INT);
}