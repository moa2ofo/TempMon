#include "ParserCore_Feed_u8.h"
#include <stddef.h>
#include <string.h>

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

/* FUNCTION TO TEST */
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