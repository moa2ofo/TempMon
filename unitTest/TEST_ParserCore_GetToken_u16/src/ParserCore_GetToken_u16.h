#ifndef TEST_PARSERCORE_GETTOKEN_U16_H
#define TEST_PARSERCORE_GETTOKEN_U16_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

_Bool ParserCore_GetToken_u16(uint16_t idx_u16, ParserCore_token_t *token_pt);
uint16_t get_TokenCnt_u16(void);
void set_TokenCnt_u16(uint16_t val);
ParserCore_token_t *get_Tokens_at_ptr(void);
size_t get_Tokens_at_size(void);
void set_Tokens_at(const ParserCore_token_t *src, size_t n);

#endif /* TEST_PARSERCORE_GETTOKEN_U16_H */
