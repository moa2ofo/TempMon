#include "IsOverEnter_b.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
extern int32_t g_OverThreshold_mC_s32;

/* FUNCTION TO TEST */
static bool IsOverEnter_b(int32_t temp_mC) {
  return (temp_mC > g_OverThreshold_mC_s32);
}