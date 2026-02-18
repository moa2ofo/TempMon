/**
 * \file ParserCore.h
 * \brief Core parser/tokenizer services.
 */

#ifndef PARSERCORE_H
#define PARSERCORE_H

#include <stdint.h>
#include <stdbool.h>

/* ======================== Public Types ======================== */

typedef enum
{
    ParserCore_tokenTypeWord_e = 0,
    ParserCore_tokenTypeNumber_e,
    ParserCore_tokenTypeSymbol_e,
    ParserCore_tokenTypeQuoted_e
} ParserCore_tokenType_e;

typedef struct
{
    ParserCore_tokenType_e type_e;
    uint16_t               start_u16;
    uint16_t               length_u16;
} ParserCore_token_t;

/* ======================== Public API ======================== */

uint32_t DemoStaticStructArray(uint16_t inc);
/**
 * \brief Initialize the parser core.
 */
void ParserCore_Init(void);

/**
 * \brief Feed one character to the parser.
 *
 * \param ch_u8 Input character (byte).
 *
 * \return true if the character was accepted, false on overflow/invalid state.
 */
bool ParserCore_Feed_u8(uint8_t ch_u8);

/**
 * \brief Finalize parsing (flush pending token, if any).
 */
void ParserCore_Finish(void);

/**
 * \brief Get number of parsed tokens currently stored.
 */
uint16_t ParserCore_GetTokenCnt_u16(void);

/**
 * \brief Get a token by index.
 *
 * \param idx_u16 Token index [0..count-1]
 * \param token_pt Output token pointer (must not be NULL)
 *
 * \return true if token exists, false otherwise.
 */

/**
 * \brief Get a pointer to the internal input buffer.
 *
 * The buffer contains all fed characters (up to capacity).
 */
const char* ParserCore_GetInputBuf_pc(void);

/* ======================== Shared Global ======================== */
/* Used by other translation units to test parser/extern resolution. */
extern uint32_t g_ParserCore_TokenCnt_u32;

#endif /* PARSERCORE_H */
