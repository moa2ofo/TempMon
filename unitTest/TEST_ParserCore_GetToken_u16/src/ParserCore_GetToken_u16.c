#include "ParserCore_GetToken_u16.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static uint16_t           TokenCnt_u16;
uint16_t get_TokenCnt_u16(void) { return TokenCnt_u16; }
void set_TokenCnt_u16(uint16_t val) { TokenCnt_u16 = val; }
static ParserCore_token_t Tokens_at[PARSERCORE_MAX_TOKENS_U16];
ParserCore_token_t* get_Tokens_at_ptr(void) { return Tokens_at; }
size_t get_Tokens_at_size(void) { return (size_t)32; }
void set_Tokens_at(const ParserCore_token_t* src, size_t n) {
    size_t m = (n < (size_t)32) ? n : (size_t)32;
    memcpy(Tokens_at, src, m * sizeof(ParserCore_token_t));
}

/* FUNCTION TO TEST */
bool ParserCore_GetToken_u16(uint16_t idx_u16, ParserCore_token_t* token_pt)
{
    bool l_ok_b = false;

    if ((token_pt != (ParserCore_token_t*)0) && (idx_u16 < TokenCnt_u16))
    {
        *token_pt = Tokens_at[idx_u16];
        l_ok_b = true;
    }

    return l_ok_b;
}