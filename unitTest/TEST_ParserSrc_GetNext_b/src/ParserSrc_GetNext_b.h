#ifndef TEST_PARSERSRC_GETNEXT_B_H
#define TEST_PARSERSRC_GETNEXT_B_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

_Bool ParserSrc_GetNext_b(uint8_t *ch_pu8);
uint16_t get_SrcIdx_u16(void);
void set_SrcIdx_u16(uint16_t val);
const char *get_SrcText_pc(void);
void set_SrcText_pc(const char *val);

#endif /* TEST_PARSERSRC_GETNEXT_B_H */
