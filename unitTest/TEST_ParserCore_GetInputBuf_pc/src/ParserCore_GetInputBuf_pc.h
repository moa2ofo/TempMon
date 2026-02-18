#ifndef TEST_PARSERCORE_GETINPUTBUF_PC_H
#define TEST_PARSERCORE_GETINPUTBUF_PC_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

const char *ParserCore_GetInputBuf_pc(void);
char *get_InputBuf_ac_ptr(void);
size_t get_InputBuf_ac_size(void);
void set_InputBuf_ac(const char *src, size_t n);

#endif /* TEST_PARSERCORE_GETINPUTBUF_PC_H */
