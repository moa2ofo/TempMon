#include "EndCurrentToken_b.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
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