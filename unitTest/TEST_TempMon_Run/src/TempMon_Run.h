

#ifndef BUILDTBL_H
#define BUILDTBL_H

#include <stdint.h>

typedef enum {
  TEMPMON_STS_NORMAL = 0,
  TEMPMON_STS_UNDER,
  TEMPMON_STS_OVER
} TempMon_sts_e;

extern TempMon_sts_e Sts_e;

void TempMon_Run(int32_t temp_mC);

#endif