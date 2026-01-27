#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  switch (TempMon_sts_e) {
  case NORMAL:
    if (temp_mC < g_UnderThreshold_mC_s32) {
      TempMon_sts_e = UNDER;
    } else if (temp_mC > g_OverThreshold_mC_s32) {
      TempMon_sts_e = OVER;
    }
    /* else remain NORMAL */
    break;

  case UNDER:
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    }
    /* else remain UNDER */
    break;

  case OVER:
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    }
    /* else remain OVER */
    break;

  default:
    /* No action for undefined states */
    break;
  }
}
