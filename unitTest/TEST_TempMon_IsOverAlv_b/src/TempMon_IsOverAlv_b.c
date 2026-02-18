#include "TempMon_IsOverAlv_b.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static TempMon_sts_e Sts_e;
TempMon_sts_e get_Sts_e(void) { return Sts_e; }
void set_Sts_e(TempMon_sts_e val) { Sts_e = val; }

/* FUNCTION TO TEST */
bool TempMon_IsOverAlv_b(void) { return (Sts_e == TEMPMON_STS_OVER); }