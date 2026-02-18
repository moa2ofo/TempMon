#ifndef TEST_DEMOSTATICSTRUCTARRAY_H
#define TEST_DEMOSTATICSTRUCTARRAY_H

#include "ParserApp.h"
#include "ParserCore.h"
#include "ParserSrc.h"
#include "TempMon.h"
#include "TempMon_priv.h"

#include <stddef.h>
#include <string.h>

uint32_t DemoStaticStructArray(uint16_t inc);
TraceEntry_t *get_g_trace_table_ptr(void);
size_t get_g_trace_table_size(void);
void set_g_trace_table(const TraceEntry_t *src, size_t n);
const TraceEntry_t *get_g_trace_table_ro_ptr(void);
size_t get_g_trace_table_ro_size(void);
void set_g_trace_table_ro(const const TraceEntry_t *src, size_t n);

#endif /* TEST_DEMOSTATICSTRUCTARRAY_H */
