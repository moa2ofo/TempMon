#ifndef TEST_PARSERSRC_INIT_H
#define TEST_PARSERSRC_INIT_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

void ParserSrc_Init(void);
uint16_t get_SrcIdx_u16(void);
void set_SrcIdx_u16(uint16_t val);

#endif /* TEST_PARSERSRC_INIT_H */
