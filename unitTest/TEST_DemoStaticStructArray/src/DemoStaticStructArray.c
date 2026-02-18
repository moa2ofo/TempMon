#include "DemoStaticStructArray.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static TraceEntry_t g_trace_table[4] = {
    {.id = 1u, .state = 0u, .flags = 0x01u, .counter = 10u},
    {.id = 2u, .state = 1u, .flags = 0x02u, .counter = 20u},
    {.id = 3u, .state = 2u, .flags = 0x04u, .counter = 30u},
    {.id = 4u, .state = 3u, .flags = 0x08u, .counter = 40u},
};
TraceEntry_t *get_g_trace_table_ptr(void) { return g_trace_table; }
size_t get_g_trace_table_size(void) { return (size_t)4; }
void set_g_trace_table(const TraceEntry_t *src, size_t n) {
  size_t m = (n < (size_t)4) ? n : (size_t)4;
  memcpy(g_trace_table, src, m * sizeof(TraceEntry_t));
}
static const TraceEntry_t g_trace_table_ro[2] = {
    {.id = 100u, .state = 9u, .flags = 0xAAu, .counter = 999u},
    {.id = 200u, .state = 8u, .flags = 0x55u, .counter = 888u},
};
const TraceEntry_t *get_g_trace_table_ro_ptr(void) { return g_trace_table_ro; }
size_t get_g_trace_table_ro_size(void) { return (size_t)2; }
void set_g_trace_table_ro(const const TraceEntry_t *src, size_t n) {
  size_t m = (n < (size_t)2) ? n : (size_t)2;
  memcpy(g_trace_table_ro, src, m * sizeof(const TraceEntry_t));
}

/* FUNCTION TO TEST */
uint32_t DemoStaticStructArray(uint16_t inc) {
  g_trace_table[0].counter += (uint32_t)inc;

  /* usa anche l'array const */
  return g_trace_table[0].counter + g_trace_table_ro[1].counter;
}