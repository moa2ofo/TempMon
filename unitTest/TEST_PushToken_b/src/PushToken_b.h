#ifndef TEST_PUSHTOKEN_B_H
#define TEST_PUSHTOKEN_B_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

_Bool PushToken_b(ParserCore_tokenType_e type_e, uint16_t start_u16, uint16_t length_u16);
uint16_t get_TokenCnt_u16(void);
void set_TokenCnt_u16(uint16_t val);
ParserCore_token_t* get_Tokens_at_ptr(void);
size_t get_Tokens_at_size(void);
void set_Tokens_at(const ParserCore_token_t* src, size_t n);

#endif /* TEST_PUSHTOKEN_B_H */
