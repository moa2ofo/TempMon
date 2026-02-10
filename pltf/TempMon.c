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

void TempMon_Run(int32_t temp_mC)
{
    /* The function updates the static status variable Sts_e based on the current temperature temp_mC
       and the external threshold and hysteresis values.
       The status can be TEMPMON_STS_NORMAL, TEMPMON_STS_UNDER, or TEMPMON_STS_OVER.
       The logic follows the activity diagram described in the header. */

    if (Sts_e == TEMPMON_STS_NORMAL)
    {
        if (temp_mC < g_UnderThreshold_mC_s32)
        {
            Sts_e = TEMPMON_STS_UNDER;
        }
        else if (temp_mC > g_OverThreshold_mC_s32)
        {
            Sts_e = TEMPMON_STS_OVER;
        }
        /* else stay TEMPMON_STS_NORMAL */
    }
    else if (Sts_e == TEMPMON_STS_UNDER)
    {
        if (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32))
        {
            Sts_e = TEMPMON_STS_NORMAL;
        }
        /* else stay TEMPMON_STS_UNDER */
    }
    else /* Sts_e == TEMPMON_STS_OVER */
    {
        if (temp_mC < (g_OverThreshold_mC_s32 - g_Hyst_mC_s32))
        {
            Sts_e = TEMPMON_STS_NORMAL;
        }
        /* else stay TEMPMON_STS_OVER */
    }
}
TempMon_sts_e TempMon_GetSts(void) { return Sts_e; }

bool TempMon_IsUnderAlv_b(void) { return (Sts_e == TEMPMON_STS_UNDER); }

bool TempMon_IsOverAlv_b(void) { return (Sts_e == TEMPMON_STS_OVER); }
