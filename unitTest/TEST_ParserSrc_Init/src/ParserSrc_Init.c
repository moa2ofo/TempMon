#include "ParserSrc_Init.h"
#include <stddef.h>
#include <string.h>

/* globals used (real definitions) */
extern uint32_t g_ParserCore_TokenCnt_u32;

/* static globals (copied) */
static uint16_t SrcIdx_u16;
uint16_t get_SrcIdx_u16(void) { return SrcIdx_u16; }
void set_SrcIdx_u16(uint16_t val) { SrcIdx_u16 = val; }

/* FUNCTION TO TEST */
void ParserSrc_Init(void)
{
    SrcIdx_u16 = 0u;

    /* Use the core global variable to prove extern linkage works */
    if (g_ParserCore_TokenCnt_u32 != 0u)
    {
        /* do nothing, just a reference for parser tests */
    }
}