#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  if (Sts_e == TEMPMON_STS_NORMAL) {
    if (temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    } else {
      if (temp_mC > g_OverThreshold_mC_s32) {
        Sts_e = TEMPMON_STS_OVER;
      } else {
        /* remain TEMPMON_STS_NORMAL */
      }
    }
  } else if (Sts_e == TEMPMON_STS_UNDER) {
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* remain TEMPMON_STS_UNDER */
    }
  } else /* Sts_e == TEMPMON_STS_OVER */
  {
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* remain TEMPMON_STS_OVER */
    }
  }
}
