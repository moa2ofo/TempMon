#include "TempMon_IsUnderAlv_b.h"
#include <stddef.h>
#include <string.h>

/* all non- globals from this TU (real definitions) */
int32_t g_Hyst_mC_s32;
int32_t g_OverThreshold_mC_s32;
int32_t g_UnderThreshold_mC_s32;

/*  globals (copied) */
 TempMon_sts_e Sts_e;
TempMon_sts_e get_Sts_e(void) { return Sts_e; }
void set_Sts_e(TempMon_sts_e val) { Sts_e = val; }

/* FUNCTION TO TEST */


bool TempMon_IsUnderAlv_b(void) {
  return (Sts_e == TEMPMON_STS_UNDER);
}
