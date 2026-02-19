#include "ParserCore_GetInputBuf_pc.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static char InputBuf_ac[PARSERCORE_INPUT_CAP_U16];
char *get_InputBuf_ac_ptr(void) {
  return InputBuf_ac;
}
size_t get_InputBuf_ac_size(void) {
  return (size_t)256;
}
void set_InputBuf_ac(const char *src, size_t n) {
  size_t m = (n < (size_t)256) ? n : (size_t)256;
  memcpy(InputBuf_ac, src, m * sizeof(char));
}

/* FUNCTION TO TEST */
const char *ParserCore_GetInputBuf_pc(void) {
  return &InputBuf_ac[0];
}