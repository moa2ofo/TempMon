#include "TempMon_Run.h"
#include "TempMon.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;
int32_t g_UnderThreshold_mC_s32 = 0;
int32_t g_OverThreshold_mC_s32 = 0;
int32_t g_Hyst_mC_s32 = 0;

/* FUNCTION TO TEST */


void TempMon_Run(int32_t temp_mC) {
  /* The function updates the static status variable Sts_e based on the current temperature temp_mC
       and the external threshold and hysteresis values.
       The status can be TEMPMON_STS_NORMAL, TEMPMON_STS_UNDER, or TEMPMON_STS_OVER.
       The logic follows the activity diagram described in the header. */

  if(Sts_e == TEMPMON_STS_NORMAL) {
    if(temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    } else if(temp_mC > g_OverThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_OVER;
    }
    /* else stay TEMPMON_STS_NORMAL */
  } else if(Sts_e == TEMPMON_STS_UNDER) {
    if(temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    }
    /* else stay TEMPMON_STS_UNDER */
  } else /* Sts_e == TEMPMON_STS_OVER */
  {
    if(temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    }
    /* else stay TEMPMON_STS_OVER */
  }
}
