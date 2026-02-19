/**
 * \file ParserSrc.c
 * \brief Implementation of input source provider.
 */

#include "ParserSrc.h"
#include "ParserCore.h" /* demonstrate cross-module include + usage */

static const char *SrcText_pc = "alpha 123 _id \"quoted value\" + - * / end";

static uint16_t SrcIdx_u16;
static uint8_t g_trace_buf[16] = {0};       /* array non-const -> getter ptr + size + setter memcpy */
static const uint32_t g_magic = 0xA5A5A5A5; /* const scalare -> solo getter */

void ParserSrc_Init(void) {
  SrcIdx_u16 = 0u;

  /* Use the core global variable to prove extern linkage works */
  if(g_ParserCore_TokenCnt_u32 != 0u) {
    /* do nothing, just a reference for parser tests */
  }
}

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

const char *ParserSrc_GetText_pc(void) {
  return SrcText_pc;
}
