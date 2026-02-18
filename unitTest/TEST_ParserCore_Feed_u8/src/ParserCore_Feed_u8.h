#ifndef TEST_PARSERCORE_FEED_U8_H
#define TEST_PARSERCORE_FEED_U8_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

_Bool ParserCore_Feed_u8(uint8_t ch_u8);
char* get_InputBuf_ac_ptr(void);
size_t get_InputBuf_ac_size(void);
void set_InputBuf_ac(const char* src, size_t n);
uint16_t get_InputLen_u16(void);
void set_InputLen_u16(uint16_t val);
Tokenize_state_e get_State_e(void);
void set_State_e(Tokenize_state_e val);
uint16_t get_TokStart_u16(void);
void set_TokStart_u16(uint16_t val);

#endif /* TEST_PARSERCORE_FEED_U8_H */
