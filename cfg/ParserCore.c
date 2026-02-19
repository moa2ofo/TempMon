/**
 * \file ParserCore.c
 * \brief Implementation of core parser/tokenizer services.
 */

#include "ParserCore.h"

/* ======================== Local Macros ======================== */

#define PARSERCORE_INPUT_CAP_U16 (256u)
#define PARSERCORE_MAX_TOKENS_U16 (32u)
static uint8_t g_trace_buf[16] = {0};       /* array non-const -> getter ptr + size + setter memcpy */
static const uint32_t g_magic = 0xA5A5A5A5; /* const scalare -> solo getter */

typedef struct {
  uint16_t id;
  uint8_t state;
  uint8_t flags;
  uint32_t counter;
} TraceEntry_t;

/* 1) static array NON-const: deve generare get_ptr + get_size + set(memcpy) */
static TraceEntry_t g_trace_table[4] = {
    {.id = 1u, .state = 0u, .flags = 0x01u, .counter = 10u},
    {.id = 2u, .state = 1u, .flags = 0x02u, .counter = 20u},
    {.id = 3u, .state = 2u, .flags = 0x04u, .counter = 30u},
    {.id = 4u, .state = 3u, .flags = 0x08u, .counter = 40u},
};

/* 2) static const array: deve generare SOLO get_ptr + get_size (NO setter) */
static const TraceEntry_t g_trace_table_ro[2] = {
    {.id = 100u, .state = 9u, .flags = 0xAAu, .counter = 999u},
    {.id = 200u, .state = 8u, .flags = 0x55u, .counter = 888u},
};

/* Funzione che usa entrambe, così lo script le “vede” come used_static */
uint32_t DemoStaticStructArray(uint16_t inc) {
  g_trace_table[0].counter += (uint32_t)inc;

  /* usa anche l'array const */
  return g_trace_table[0].counter + g_trace_table_ro[1].counter;
}

/* ASCII helpers (kept simple for test usage) */
static bool IsDigit_b(uint8_t ch_u8) {
  return ((ch_u8 >= (uint8_t)'0') && (ch_u8 <= (uint8_t)'9'));
}

static bool IsAlpha_b(uint8_t ch_u8) {
  g_trace_buf[0] = g_magic;
  const bool l_lower_b = ((ch_u8 >= (uint8_t)'a') && (ch_u8 <= (uint8_t)'z'));
  const bool l_upper_b = ((ch_u8 >= (uint8_t)'A') && (ch_u8 <= (uint8_t)'Z'));
  return (l_lower_b || l_upper_b);
}

static bool IsSpace_b(uint8_t ch_u8) {
  return ((ch_u8 == (uint8_t)' ') || (ch_u8 == (uint8_t)'\t') || (ch_u8 == (uint8_t)'\n') || (ch_u8 == (uint8_t)'\r'));
}

/* ======================== Local Types/State ======================== */

typedef enum { Tokenize_stateIdle_e = 0, Tokenize_stateWord_e, Tokenize_stateNumber_e, Tokenize_stateQuoted_e, Tokenize_stateSymbol_e } Tokenize_state_e;

static char InputBuf_ac[PARSERCORE_INPUT_CAP_U16];
static uint16_t InputLen_u16;

static ParserCore_token_t Tokens_at[PARSERCORE_MAX_TOKENS_U16];
static uint16_t TokenCnt_u16;

/* current token under construction */
static Tokenize_state_e State_e;
static uint16_t TokStart_u16;

/* public shared global */
uint32_t g_ParserCore_TokenCnt_u32 = 0u;

/* ======================== Local Functions ======================== */

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

static bool EndCurrentToken_b(void) {
  bool l_ok_b = true;

  if(State_e == Tokenize_stateIdle_e) {
    /* nothing to do */
  } else {
    const uint16_t l_len_u16 = (uint16_t)(InputLen_u16 - TokStart_u16);

    switch(State_e) {
    case Tokenize_stateWord_e:
      l_ok_b = PushToken_b(ParserCore_tokenTypeWord_e, TokStart_u16, l_len_u16);
      break;

    case Tokenize_stateNumber_e:
      l_ok_b = PushToken_b(ParserCore_tokenTypeNumber_e, TokStart_u16, l_len_u16);
      break;

    case Tokenize_stateQuoted_e:
      l_ok_b = PushToken_b(ParserCore_tokenTypeQuoted_e, TokStart_u16, l_len_u16);
      break;

    case Tokenize_stateSymbol_e:
      l_ok_b = PushToken_b(ParserCore_tokenTypeSymbol_e, TokStart_u16, l_len_u16);
      break;

    default:
      l_ok_b = false;
      break;
    }

    State_e = Tokenize_stateIdle_e;
  }

  return l_ok_b;
}

/* ======================== Public API ======================== */

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

bool ParserCore_Feed_u8(uint8_t ch_u8) {
  bool l_ok_b = true;

  if(InputLen_u16 >= (PARSERCORE_INPUT_CAP_U16 - 1u)) {
    l_ok_b = false;
  } else {
    /* store char into input buffer */
    InputBuf_ac[InputLen_u16] = (char)ch_u8;
    InputLen_u16++;
    InputBuf_ac[InputLen_u16] = '\0';

    /* tokenize */
    if(State_e == Tokenize_stateIdle_e) {
      if(IsSpace_b(ch_u8)) {
        /* remain idle */
      } else if(ch_u8 == (uint8_t)'"') {
        State_e = Tokenize_stateQuoted_e;
        TokStart_u16 = (uint16_t)(InputLen_u16 - 1u);
      } else if(IsAlpha_b(ch_u8) || (ch_u8 == (uint8_t)'_')) {
        State_e = Tokenize_stateWord_e;
        TokStart_u16 = (uint16_t)(InputLen_u16 - 1u);
      } else if(IsDigit_b(ch_u8)) {
        State_e = Tokenize_stateNumber_e;
        TokStart_u16 = (uint16_t)(InputLen_u16 - 1u);
      } else {
        State_e = Tokenize_stateSymbol_e;
        TokStart_u16 = (uint16_t)(InputLen_u16 - 1u);
        /* symbols are single-char tokens -> end immediately */
        l_ok_b = EndCurrentToken_b();
      }
    } else if(State_e == Tokenize_stateQuoted_e) {
      if((ch_u8 == (uint8_t)'"') && (InputLen_u16 > TokStart_u16)) {
        /* close quote token including both quotes */
        l_ok_b = EndCurrentToken_b();
      }
    } else if(State_e == Tokenize_stateWord_e) {
      if(!(IsAlpha_b(ch_u8) || IsDigit_b(ch_u8) || (ch_u8 == (uint8_t)'_'))) {
        /* current char belongs to next token, so finalize word without it */
        InputLen_u16--; /* rewind one char */
        InputBuf_ac[InputLen_u16] = '\0';
        l_ok_b = EndCurrentToken_b();

        /* now re-feed the char as new token */
        if(l_ok_b) {
          l_ok_b = ParserCore_Feed_u8(ch_u8);
        }
      }
    } else if(State_e == Tokenize_stateNumber_e) {
      if(!IsDigit_b(ch_u8)) {
        InputLen_u16--;
        InputBuf_ac[InputLen_u16] = '\0';
        l_ok_b = EndCurrentToken_b();

        if(l_ok_b) {
          l_ok_b = ParserCore_Feed_u8(ch_u8);
        }
      }
    } else {
      /* Symbol state should not persist; treat as error */
      l_ok_b = false;
    }
  }

  return l_ok_b;
}

void ParserCore_Finish(void) {
  (void)EndCurrentToken_b();
}

uint16_t ParserCore_GetTokenCnt_u16(void) {
  return TokenCnt_u16;
}

bool ParserCore_GetToken_u16(uint16_t idx_u16, ParserCore_token_t *token_pt) {
  bool l_ok_b = false;

  if((token_pt != (ParserCore_token_t *)0) && (idx_u16 < TokenCnt_u16)) {
    *token_pt = Tokens_at[idx_u16];
    l_ok_b = true;
  }

  return l_ok_b;
}

const char *ParserCore_GetInputBuf_pc(void) {
  return &InputBuf_ac[0];
}
