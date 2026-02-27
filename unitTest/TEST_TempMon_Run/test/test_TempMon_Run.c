#include "TempMon.h"
#include "TempMon_Run.h"
#include "mock_TempMon_priv.h"
#include "unity.h"
#include <string.h>




static TempMonstse Sts_e;

static TempMonstse TempMonGetStsCallback(int call_count)
{
    return Sts_e;
}

static void TempMonInitCallback(int32t tempmC, int call_count)
{
    if (tempmC < gUnderThresholdmCs32)
    {
        Stse = TEMPMONSTS_UNDER;
    }
    else if (tempmC > gOverThresholdmCs32)
    {
        Stse = TEMPMONSTS_OVER;
    }
    else
    {
        Stse = TEMPMONSTS_NORMAL;
    }
}

static bool IsUnderEnterbCallback(int32t tempmC, int call_count)
{
    return (tempmC < gUnderThresholdmCs32);
}

static bool IsUnderExitbCallback(int32t tempmC, int call_count)
{
    return (tempmC > (gUnderThresholdmCs32 + gHystmC_s32));
}

static bool IsOverEnterbCallback(int32t tempmC, int call_count)
{
    return (tempmC > gOverThresholdmCs32);
}

static bool IsOverExitbCallback(int32t tempmC, int call_count)
{
    return (tempmC < (gOverThresholdmCs32 - gHystmC_s32));
}

void setUp(void)
{
    Stse = TEMPMONSTS_NORMAL;
    gUnderThresholdmC_s32 = 0;
    gOverThresholdmC_s32 = 0;
    gHystmC_s32 = 0;
    
    TempMonInitStub(TempMonInitCallback);
    TempMonGetStsStub(TempMonGetStsCallback);
    IsUnderEnterbStub(IsUnderEnterbCallback);
    IsUnderExitbStub(IsUnderExitbCallback);
    IsOverEnterbStub(IsOverEnterbCallback);
    IsOverExitbStub(IsOverExitbCallback);
}

void tearDown(void)
{
}

void testNormalToUnderBelowThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(9999);
    
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testNormalStaysEqualUnderThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(10000);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysJustAboveUnderThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(10001);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysMidRange(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(30000);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysJustBelowOverThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(49999);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysEqualOverThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(50000);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalToOverAboveThreshold(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(50001);
    
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}

void testUnderStaysBelowRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(12000);
    
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testUnderStaysEqualRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(12000);
    
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testUnderToNormalAboveRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(12001);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testOverStaysAboveRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(48001);
    
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}

void testOverStaysEqualRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(48000);
    
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}

void testOverToNormalBelowRecovery(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(47999);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalToUnderZeroHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 0;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(9999);
    
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testUnderToNormalZeroHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 0;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(10001);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalToOverZeroHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 0;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(50001);
    
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}

void testOverToNormalZeroHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 0;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(49999);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysMaxTemp_MaxOver(void)
{
    gUnderThresholdmC_s32 = 0;
    gOverThresholdmC_s32 = 2147483647;
    gHystmC_s32 = 1000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(2147483647);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalStaysMinTemp_MinUnder(void)
{
    gUnderThresholdmC_s32 = -2147483648;
    gOverThresholdmC_s32 = 0;
    gHystmC_s32 = 1000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(-2147483648);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testUnderToNormalMaxTemp(void)
{
    gUnderThresholdmC_s32 = 2147483640;
    gOverThresholdmC_s32 = 2147483647;
    gHystmC_s32 = 5;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(2147483647);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testOverToNormalMinTemp(void)
{
    gUnderThresholdmC_s32 = -2147483648;
    gOverThresholdmC_s32 = -2147483640;
    gHystmC_s32 = 5;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(-2147483648);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testNormalToUnderEqualThresholds_Below(void)
{
    gUnderThresholdmC_s32 = 25000;
    gOverThresholdmC_s32 = 25000;
    gHystmC_s32 = 1000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(24999);
    
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testNormalToOverEqualThresholds_Above(void)
{
    gUnderThresholdmC_s32 = 25000;
    gOverThresholdmC_s32 = 25000;
    gHystmC_s32 = 1000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(25001);
    
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}

void testNormalStaysEqualThresholds_Equal(void)
{
    gUnderThresholdmC_s32 = 25000;
    gOverThresholdmC_s32 = 25000;
    gHystmC_s32 = 1000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(25000);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testUnderToNormalLargeHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 20000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(30001);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testOverToNormalLargeHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 20000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(29999);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testUnderToNormalNegativeHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = -2000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(8001);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testOverToNormalNegativeHyst(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = -2000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(51999);
    
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testPersistenceNormal(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_NORMAL;
    
    TempMon_Run(30000);
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
    
    TempMon_Run(30000);
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
    
    TempMon_Run(30000);
    TESTASSERTEQUAL(TEMPMONSTSNORMAL, Sts_e);
}

void testPersistenceUnder(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_UNDER;
    
    TempMon_Run(5000);
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
    
    TempMon_Run(5000);
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
    
    TempMon_Run(5000);
    TESTASSERTEQUAL(TEMPMONSTSUNDER, Sts_e);
}

void testPersistenceOver(void)
{
    gUnderThresholdmC_s32 = 10000;
    gOverThresholdmC_s32 = 50000;
    gHystmC_s32 = 2000;
    
    Stse = TEMPMONSTS_OVER;
    
    TempMon_Run(60000);
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
    
    TempMon_Run(60000);
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
    
    TempMon_Run(60000);
    TESTASSERTEQUAL(TEMPMONSTSOVER, Sts_e);
}