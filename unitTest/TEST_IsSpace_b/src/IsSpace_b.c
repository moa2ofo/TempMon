#include "IsSpace_b.h"
#include <stddef.h>
#include <string.h>

/* FUNCTION TO TEST */
static bool IsSpace_b(uint8_t ch_u8) { return ((ch_u8 == (uint8_t)' ') || (ch_u8 == (uint8_t)'\t') || (ch_u8 == (uint8_t)'\n') || (ch_u8 == (uint8_t)'\r')); }