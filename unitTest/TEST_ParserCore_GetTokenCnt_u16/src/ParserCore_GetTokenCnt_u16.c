#include "ParserCore_GetTokenCnt_u16.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static uint16_t           TokenCnt_u16;
uint16_t get_TokenCnt_u16(void) { return TokenCnt_u16; }
void set_TokenCnt_u16(uint16_t val) { TokenCnt_u16 = val; }

/* FUNCTION TO TEST */
uint16_t ParserCore_GetTokenCnt_u16(void)
{
    return TokenCnt_u16;
}