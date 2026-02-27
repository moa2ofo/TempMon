#include "IsUnderExit_b.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
int32_t g_Hyst_mC_s32;
int32_t g_UnderThreshold_mC_s32;

/* FUNCTION TO TEST */


bool IsUnderExit_b(int32_t temp_mC) {
  return (temp_mC > (g_UnderThreshold_mC_s32 + g_Hyst_mC_s32));
}
