#include "TempMon_Run.h"
#include "TempMon.h"
#include "TempMon_priv.h"

int32_t g_UnderThreshold_mC_s32 = 0;    /* e.g. 0.000°C */
int32_t g_OverThreshold_mC_s32 = 85000; /* e.g. 85.000°C */
int32_t g_Hyst_mC_s32 = 2000;           /* e.g. 2.000°C */
TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  if (Sts_e == TEMPMON_STS_NORMAL) {
    if (temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    } else if (temp_mC > g_OverThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_OVER;
    } else {
      /* Remain in TEMPMON_STS_NORMAL */
    }
  } else if (Sts_e == TEMPMON_STS_UNDER) {
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* Remain in TEMPMON_STS_UNDER */
    }
  } else /* TEMPMON_STS_OVER */
  {
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    } else {
      /* Remain in TEMPMON_STS_OVER */
    }
  }
}
