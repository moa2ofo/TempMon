/**
 * \file ParserApp.c
 * \brief Demo app wiring ParserSrc + ParserCore.
 */

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"

#include <stdio.h>
static uint8_t g_trace_buf[16] = {0};       /* array non-const -> getter ptr + size + setter memcpy */
static const uint32_t g_magic = 0xA5A5A5A5; /* const scalare -> solo getter */

static void PrintToken(const ParserCore_token_t *token_pt) {
  const char *l_buf_pc = ParserCore_GetInputBuf_pc();
  uint16_t l_i_u16;

  (void)printf("type=%u start=%u len=%u text=\"", (unsigned)token_pt->type_e, (unsigned)token_pt->start_u16, (unsigned)token_pt->length_u16);

  for(l_i_u16 = 0u; l_i_u16 < token_pt->length_u16; l_i_u16++) {
    const char l_ch_c = l_buf_pc[(uint16_t)(token_pt->start_u16 + l_i_u16)];
    (void)putchar((int)l_ch_c);
  }

  (void)printf("\"\n");
}

int32_t ParserApp_Run_s32(void) {
  int32_t l_rc_s32 = 0;
  uint8_t l_ch_u8;
  bool l_ok_b;

  ParserCore_Init();
  ParserSrc_Init();

  /* bounded loop: stop when source ends (guaranteed) */
  do {
    l_ok_b = ParserSrc_GetNext_b(&l_ch_u8);
    if(l_ok_b) {
      const bool l_feedOk_b = ParserCore_Feed_u8(l_ch_u8);
      if(!l_feedOk_b) {
        l_rc_s32 = 2;
        l_ok_b = false; /* stop */
      }
    }
  } while(l_ok_b);

  ParserCore_Finish();

  /* print tokens */
  {
    const uint16_t l_cnt_u16 = ParserCore_GetTokenCnt_u16();
    uint16_t l_idx_u16;

    (void)printf("Source: %s\n", ParserSrc_GetText_pc());
    (void)printf("Tokens=%u (global=%lu)\n", (unsigned)l_cnt_u16, (unsigned long)g_ParserCore_TokenCnt_u32);

    for(l_idx_u16 = 0u; l_idx_u16 < l_cnt_u16; l_idx_u16++) {
      ParserCore_token_t l_tok_t;
      const bool l_has_b = ParserCore_GetToken_u16(l_idx_u16, &l_tok_t);
      if(l_has_b) {
        PrintToken(&l_tok_t);
      } else {
        l_rc_s32 = 3;
      }
    }
  }

  return l_rc_s32;
}

int main(void) {
  const int32_t l_rc_s32 = ParserApp_Run_s32();
  return (int)l_rc_s32;
}
