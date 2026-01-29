/* TempMon.c */

#include "TempMon.h"

static TempMon_sts_e Sts_e;
/* ===== Public configuration (defaults) ===== */
int32_t g_UnderThreshold_mC_s32 = 0;    /* e.g. 0.000°C */
int32_t g_OverThreshold_mC_s32 = 85000; /* e.g. 85.000°C */
int32_t g_Hyst_mC_s32 = 2000;           /* e.g. 2.000°C */

/* ===== Private helpers =====
 * Hysteresis behavior:
 * - Enter UNDER when temp < UnderThreshold
 * - Exit  UNDER when temp > UnderThreshold + Hyst
 *
 * - Enter OVER  when temp > OverThreshold
 * - Exit  OVER  when temp < OverThreshold - Hyst
 */

static bool IsUnderEnter_b(int32_t temp_mC) { return (temp_mC < g_UnderThreshold_mC_s32); }

static bool IsUnderExit_b(int32_t temp_mC) { return (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)); }

static bool IsOverEnter_b(int32_t temp_mC) { return (temp_mC > g_OverThreshold_mC_s32); }

static bool IsOverExit_b(int32_t temp_mC) { return (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)); }

void TempMon_Init(int32_t temp_mC) {
  /* Determine initial state using same rules of the state machine */
  Sts_e = TEMPMON_STS_NORMAL;
  TempMon_Run(temp_mC);
}

void TempMon_Run(const int32_t temp_mC) {
  /* Start of TempMon_Run function */

  /* Update state machine based on current state and temperature */

  switch(Sts_e) {
  case TEMPMON_STS_NORMAL:
    /* If temperature below under threshold, enter UNDER state */
    if(temp_mC < g_UnderThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_UNDER;
    }
    /* Else if temperature above over threshold, enter OVER state */
    else if(temp_mC > g_OverThreshold_mC_s32) {
      Sts_e = TEMPMON_STS_OVER;
    }
    /* Else remain in NORMAL state */
    else {
      /* Remain in TEMPMON_STS_NORMAL */
    }
    break;

  case TEMPMON_STS_UNDER:
    /* If temperature above under threshold plus hysteresis, return to NORMAL */
    if(temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32)) {
      Sts_e = TEMPMON_STS_NORMAL;
    }
    /* Else remain in UNDER state */
    else {
      /* Remain in TEMPMON_STS_UNDER */
    }
    break;

  case TEMPMON_STS_OVER:
    /* If temperature below over threshold minus hysteresis, return to NORMAL */
    if(temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32)) {
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
TempMon_sts_e TempMon_GetSts(void) { return Sts_e; }

bool TempMon_IsUnderAlv_b(void) { return (Sts_e == TEMPMON_STS_UNDER); }

bool TempMon_IsOverAlv_b(void) { return (Sts_e == TEMPMON_STS_OVER); }
