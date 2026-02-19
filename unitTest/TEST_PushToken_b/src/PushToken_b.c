#include "PushToken_b.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
uint32_t g_ParserCore_TokenCnt_u32 = 0u;

/* static globals (copied) */
static uint16_t TokenCnt_u16;
uint16_t get_TokenCnt_u16(void) {
  return TokenCnt_u16;
}
void set_TokenCnt_u16(uint16_t val) {
  TokenCnt_u16 = val;
}
static ParserCore_token_t Tokens_at[PARSERCORE_MAX_TOKENS_U16];
ParserCore_token_t *get_Tokens_at_ptr(void) {
  return Tokens_at;
}
size_t get_Tokens_at_size(void) {
  return (size_t)32;
}
void set_Tokens_at(const ParserCore_token_t *src, size_t n) {
  size_t m = (n < (size_t)32) ? n : (size_t)32;
  memcpy(Tokens_at, src, m * sizeof(ParserCore_token_t));
}

/* FUNCTION TO TEST */
static bool PushToken_b(ParserCore_tokenType_e type_e, uint16_t start_u16, uint16_t length_u16) {
  bool l_ok_b = true;

  if((length_u16 == 0u) || (TokenCnt_u16 >= PARSERCORE_MAX_TOKENS_U16)) {
    l_ok_b = false;
  } else {
    Tokens_at[TokenCnt_u16].type_e = type_e;
    Tokens_at[TokenCnt_u16].start_u16 = start_u16;
    Tokens_at[TokenCnt_u16].length_u16 = length_u16;
    TokenCnt_u16++;

    /* update global for cross-module access */
    g_ParserCore_TokenCnt_u32 = (uint32_t)TokenCnt_u16;
  }

  return l_ok_b;
}