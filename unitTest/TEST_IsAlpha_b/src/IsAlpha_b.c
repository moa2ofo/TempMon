#include "IsAlpha_b.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static const uint32_t g_magic = 0xA5A5A5A5;
const uint32_t get_g_magic(void) { return g_magic; }
static uint8_t g_trace_buf[16] = {0};
uint8_t *get_g_trace_buf_ptr(void) { return g_trace_buf; }
size_t get_g_trace_buf_size(void) { return (size_t)16; }
void set_g_trace_buf(const uint8_t *src, size_t n) {
  size_t m = (n < (size_t)16) ? n : (size_t)16;
  memcpy(g_trace_buf, src, m * sizeof(uint8_t));
}

/* FUNCTION TO TEST */
static bool IsAlpha_b(uint8_t ch_u8) {
  g_trace_buf[0] = g_magic;
  const bool l_lower_b = ((ch_u8 >= (uint8_t)'a') && (ch_u8 <= (uint8_t)'z'));
  const bool l_upper_b = ((ch_u8 >= (uint8_t)'A') && (ch_u8 <= (uint8_t)'Z'));
  return (l_lower_b || l_upper_b);
}