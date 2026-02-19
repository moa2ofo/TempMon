#include "TempMon_Init.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static TempMon_sts_e Sts_e;
TempMon_sts_e get_Sts_e(void) {
  return Sts_e;
}
void set_Sts_e(TempMon_sts_e val) {
  Sts_e = val;
}

/* FUNCTION TO TEST */
void TempMon_Init(int32_t temp_mC) {
  /* Determine initial state using same rules of the state machine */
  Sts_e = TEMPMON_STS_NORMAL;
  TempMon_Run(temp_mC);
}