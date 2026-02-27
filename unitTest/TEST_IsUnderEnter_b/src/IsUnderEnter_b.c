#include "IsUnderEnter_b.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
int32_t g_UnderThreshold_mC_s32;

/* FUNCTION TO TEST */


bool IsUnderEnter_b(int32_t temp_mC) {
  return (temp_mC < g_UnderThreshold_mC_s32);
}
