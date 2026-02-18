#include "PrintToken.h"
#include <stddef.h>
#include <string.h>

/* FUNCTION TO TEST */
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