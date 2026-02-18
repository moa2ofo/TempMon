#include "ParserCore_Init.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
uint32_t g_ParserCore_TokenCnt_u32 = 0u;

/* static globals (copied) */
static char InputBuf_ac[PARSERCORE_INPUT_CAP_U16];
char *get_InputBuf_ac_ptr(void) { return InputBuf_ac; }
size_t get_InputBuf_ac_size(void) { return (size_t)256; }
void set_InputBuf_ac(const char *src, size_t n) {
  size_t m = (n < (size_t)256) ? n : (size_t)256;
  memcpy(InputBuf_ac, src, m * sizeof(char));
}
static uint16_t InputLen_u16;
uint16_t get_InputLen_u16(void) { return InputLen_u16; }
void set_InputLen_u16(uint16_t val) { InputLen_u16 = val; }
static Tokenize_state_e State_e;
Tokenize_state_e get_State_e(void) { return State_e; }
void set_State_e(Tokenize_state_e val) { State_e = val; }
static uint16_t TokStart_u16;
uint16_t get_TokStart_u16(void) { return TokStart_u16; }
void set_TokStart_u16(uint16_t val) { TokStart_u16 = val; }
static uint16_t TokenCnt_u16;
uint16_t get_TokenCnt_u16(void) { return TokenCnt_u16; }
void set_TokenCnt_u16(uint16_t val) { TokenCnt_u16 = val; }
static ParserCore_token_t Tokens_at[PARSERCORE_MAX_TOKENS_U16];
ParserCore_token_t *get_Tokens_at_ptr(void) { return Tokens_at; }
size_t get_Tokens_at_size(void) { return (size_t)32; }
void set_Tokens_at(const ParserCore_token_t *src, size_t n) {
  size_t m = (n < (size_t)32) ? n : (size_t)32;
  memcpy(Tokens_at, src, m * sizeof(ParserCore_token_t));
}

/* FUNCTION TO TEST */
void ParserCore_Init(void) {
  uint16_t l_i_u16;

  for(l_i_u16 = 0u; l_i_u16 < PARSERCORE_INPUT_CAP_U16; l_i_u16++) {
    InputBuf_ac[l_i_u16] = '\0';
  }

  for(l_i_u16 = 0u; l_i_u16 < PARSERCORE_MAX_TOKENS_U16; l_i_u16++) {
    Tokens_at[l_i_u16].type_e = ParserCore_tokenTypeSymbol_e;
    Tokens_at[l_i_u16].start_u16 = 0u;
    Tokens_at[l_i_u16].length_u16 = 0u;
  }

  InputLen_u16 = 0u;
  TokenCnt_u16 = 0u;
  State_e = Tokenize_stateIdle_e;
  TokStart_u16 = 0u;

  g_ParserCore_TokenCnt_u32 = 0u;
}