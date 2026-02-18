#include "IsDigit_b.h"
#include <stddef.h>
#include <string.h>

/* FUNCTION TO TEST */
static bool IsDigit_b(uint8_t ch_u8)
{
    return ((ch_u8 >= (uint8_t)'0') && (ch_u8 <= (uint8_t)'9'));
}