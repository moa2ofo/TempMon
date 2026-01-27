#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  if (TempMon_sts_e == NORMAL) {
    if (temp_mC < g_UnderThreshold_mC_s32) {
      TempMon_sts_e = UNDER;
    } else if (temp_mC > g_OverThreshold_mC_s32) {
      TempMon_sts_e = OVER;
    } else {
      /* Remain NORMAL */
    }
  } else if (TempMon_sts_e == UNDER) {
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    } else {
      /* Remain UNDER */
    }
  } else /* TempMon_sts_e == OVER */
  {
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      TempMon_sts_e = NORMAL;
    } else {
      /* Remain OVER */
    }
  }
}
