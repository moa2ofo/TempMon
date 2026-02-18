#ifndef TEST_ENDCURRENTTOKEN_B_H
#define TEST_ENDCURRENTTOKEN_B_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

_Bool EndCurrentToken_b(void);
uint16_t get_InputLen_u16(void);
void set_InputLen_u16(uint16_t val);
Tokenize_state_e get_State_e(void);
void set_State_e(Tokenize_state_e val);
uint16_t get_TokStart_u16(void);
void set_TokStart_u16(uint16_t val);

#endif /* TEST_ENDCURRENTTOKEN_B_H */
