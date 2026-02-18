#ifndef TEST_TEMPMON_INIT_H
#define TEST_TEMPMON_INIT_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

void TempMon_Init(int32_t temp_mC);
TempMon_sts_e get_Sts_e(void);
void set_Sts_e(TempMon_sts_e val);

#endif /* TEST_TEMPMON_INIT_H */
