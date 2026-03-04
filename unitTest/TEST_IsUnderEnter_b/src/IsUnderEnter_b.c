#include "IsUnderEnter_b.h"
#include <stddef.h>
#include <string.h>

/* all non- globals from this TU (real definitions) */
int32_t g_Hyst_mC_s32;
int32_t g_OverThreshold_mC_s32;
int32_t g_UnderThreshold_mC_s32;

/* FUNCTION TO TEST */


bool IsUnderEnter_b(int32_t temp_mC) {
  return (temp_mC < g_UnderThreshold_mC_s32);
}
