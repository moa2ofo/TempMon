#include "ParserSrc_GetNext_b.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static uint16_t SrcIdx_u16;
uint16_t get_SrcIdx_u16(void) { return SrcIdx_u16; }
void set_SrcIdx_u16(uint16_t val) { SrcIdx_u16 = val; }
static const char *SrcText_pc = "alpha 123 _id \"quoted value\" + - * / end";
const char *get_SrcText_pc(void) { return SrcText_pc; }
void set_SrcText_pc(const char *val) { SrcText_pc = val; }

/* FUNCTION TO TEST */
bool ParserSrc_GetNext_b(uint8_t *ch_pu8) {
  bool l_ok_b = false;

  if(ch_pu8 != (uint8_t *)0) {
    const char l_ch_c = SrcText_pc[SrcIdx_u16];

    if(l_ch_c != '\0') {
      *ch_pu8 = (uint8_t)l_ch_c;
      SrcIdx_u16++;
      l_ok_b = true;
    }
  }

  return l_ok_b;
}