#include "TempMon_Run.h"
#include "TempMon.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;
int32_t g_UnderThreshold_mC_s32 = 0;
int32_t g_OverThreshold_mC_s32 = 0;
int32_t g_Hyst_mC_s32 = 0;

/* FUNCTION TO TEST */

void TempMon_Run(int32_t temp_mC) {
  /**
     * @brief Static status variable holding the current temperature monitor state.
     * Initialized to TEMPMON_STS_NORMAL.
     */
  static TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

  /* Check current state and update based on temperature and thresholds with hysteresis. */
  if(Sts_e == TEMPMON_STS_NORMAL) {
    if(temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    } else if(temp_mC > g_OverThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_OVER;
    } else {
      /* Stay in TEMPMON_STS_NORMAL state */
    }
  } else if(Sts_e == TEMPMON_STS_UNDER) {
    if(temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* Stay in TEMPMON_STS_UNDER state */
    }
  } else if(Sts_e == TEMPMON_STS_OVER) {
    if(temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* Stay in TEMPMON_STS_OVER state */
    }
  } else {
    /* Unexpected state: no action, maintain current state */
  }
}
