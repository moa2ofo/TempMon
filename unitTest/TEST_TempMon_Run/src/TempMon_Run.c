#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  /* Update state machine based on current temperature and thresholds */
  switch (TempMon_sts_e) {
  case NORMAL:
    /* Check if temperature is below under threshold */
    if (temp_mC < g_UnderThreshold_mC_s32) {
      TempMon_sts_e = UNDER;
    }
    /* Check if temperature is above over threshold */
    else if (temp_mC > g_OverThreshold_mC_s32) {
      TempMon_sts_e = OVER;
    }
    /* else remain NORMAL */
    break;

  case UNDER:
    /* Check if temperature has risen above under threshold plus hysteresis */
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    }
    /* else remain UNDER */
    break;

  case OVER:
    /* Check if temperature has fallen below over threshold minus hysteresis */
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    }
    /* else remain OVER */
    break;

  default:
    /* Undefined state: no action expected */
    break;
  }
}
