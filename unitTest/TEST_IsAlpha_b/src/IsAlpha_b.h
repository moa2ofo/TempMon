#ifndef TEST_ISALPHA_B_H
#define TEST_ISALPHA_B_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

_Bool IsAlpha_b(uint8_t ch_u8);
const uint32_t get_g_magic(void);
uint8_t* get_g_trace_buf_ptr(void);
size_t get_g_trace_buf_size(void);
void set_g_trace_buf(const uint8_t* src, size_t n);

#endif /* TEST_ISALPHA_B_H */
