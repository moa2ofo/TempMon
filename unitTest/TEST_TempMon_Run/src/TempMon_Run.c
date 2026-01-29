#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */


void TempMon_Run(const int32_t temp_mC) {
  /* Start of TempMon_Run function */

  /* Update state machine based on current state and temperature */

  switch (Sts_e) {
  case TEMPMON_STS_NORMAL:
    /* If temperature below under threshold, enter UNDER state */
    if (temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    }
    /* Else if temperature above over threshold, enter OVER state */
    else if (temp_mC > g_OverThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_OVER;
    }
    /* Else remain in NORMAL state */
    else {
      /* Remain in TEMPMON_STS_NORMAL */
    }
    break;

  case TEMPMON_STS_UNDER:
    /* If temperature above under threshold plus hysteresis, return to NORMAL */
    if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    }
    /* Else remain in UNDER state */
    else {
      /* Remain in TEMPMON_STS_UNDER */
    }
    break;

  case TEMPMON_STS_OVER:
    /* If temperature below over threshold minus hysteresis, return to NORMAL */
    if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    }
    /* Else remain in OVER state */
    else {
      /* Remain in TEMPMON_STS_OVER */
    }
    break;

  default:
    /**
     * @brief No action for undefined states.
     * This default case ensures stability if Sts_e has an unexpected value.
     */
    break;
  }

  /* End of TempMon_Run function */
}
