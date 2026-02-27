// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/TempMon.h"
#include "utExecutionAndResults/utUnderTest/src/TempMon_Run.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_TempMon_priv.h"

```

    static TempMon_sts_e callback_Sts_e;

static
      _Bool
           IsUnderEnter_b_Callback(int32_t temp_mC, int cmock_num_calls)
{
  return (temp_mC < g_UnderThreshold_mC_s32);
}

static
      _Bool
           IsUnderExit_b_Callback(int32_t temp_mC, int cmock_num_calls)
{
  return (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32));
}

static
      _Bool
           IsOverEnter_b_Callback(int32_t temp_mC, int cmock_num_calls)
{
  return (temp_mC > g_OverThreshold_mC_s32);
}

static
      _Bool
           IsOverExit_b_Callback(int32_t temp_mC, int cmock_num_calls)
{
  return (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32));
}

static TempMon_sts_e TempMon_GetSts_Callback(int cmock_num_calls)
{
  return callback_Sts_e;
}

static void TempMon_GetSts_SetReturnValue(TempMon_sts_e sts)
{
  callback_Sts_e = sts;
}

void setUp(void)
{
  callback_Sts_e = TEMPMON_STS_NORMAL;
  g_UnderThreshold_mC_s32 = -10000;
  g_OverThreshold_mC_s32 = 85000;
  g_Hyst_mC_s32 = 5000;
}

void tearDown(void)
{
}

void test_Under_LargeHyst_NoOverflow(void)
{
  TempMon_GetSts_Stub(TempMon_GetSts_Callback);
  IsUnderExit_b_Stub(IsUnderExit_b_Callback);

  TempMon_GetSts_SetReturnValue(TEMPMON_STS_UNDER);
  g_UnderThreshold_mC_s32 = -1000000;
  g_Hyst_mC_s32 = 2000000000;

  TempMon_Run(1000000001);
}