#include "ParserSrc_GetText_pc.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static const char* SrcText_pc =
    "alpha 123 _id \"quoted value\" + - * / end";
const char * get_SrcText_pc(void) { return SrcText_pc; }
void set_SrcText_pc(const char * val) { SrcText_pc = val; }

/* FUNCTION TO TEST */
const char* ParserSrc_GetText_pc(void)
{
    return SrcText_pc;
}