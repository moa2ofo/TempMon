/**
 * \file ParserSrc.h
 * \brief Input source provider for the parser (streams bytes).
 */

#ifndef PARSERSRC_H
#define PARSERSRC_H

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Initialize the source with a built-in test string.
 */
void ParserSrc_Init(void);

/**
 * \brief Get next byte from the source.
 *
 * \param ch_pu8 Output character pointer
 * \return true if a byte is available, false if end-of-source.
 */
bool ParserSrc_GetNext_b(uint8_t* ch_pu8);

/**
 * \brief Return the full source string (for debugging).
 */

#endif /* PARSERSRC_H */
