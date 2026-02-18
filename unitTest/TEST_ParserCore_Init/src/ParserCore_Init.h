#ifndef TEST_PARSERCORE_INIT_H
#define TEST_PARSERCORE_INIT_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

void ParserCore_Init(void);
char *get_InputBuf_ac_ptr(void);
size_t get_InputBuf_ac_size(void);
void set_InputBuf_ac(const char *src, size_t n);
uint16_t get_InputLen_u16(void);
void set_InputLen_u16(uint16_t val);
Tokenize_state_e get_State_e(void);
void set_State_e(Tokenize_state_e val);
uint16_t get_TokStart_u16(void);
void set_TokStart_u16(uint16_t val);
uint16_t get_TokenCnt_u16(void);
void set_TokenCnt_u16(uint16_t val);
ParserCore_token_t *get_Tokens_at_ptr(void);
size_t get_Tokens_at_size(void);
void set_Tokens_at(const ParserCore_token_t *src, size_t n);

#endif /* TEST_PARSERCORE_INIT_H */
