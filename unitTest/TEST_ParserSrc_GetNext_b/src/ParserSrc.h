/**
 * \file ParserSrc.h
 * \brief Input source provider for the parser (streams bytes).
 */

#ifndef PARSERSRC_H
#define PARSERSRC_H

#include <stdbool.h>
#include <stdint.h>

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

/**
 * \brief Return the full source string (for debugging).
 */
const char *ParserSrc_GetText_pc(void);

#endif /* PARSERSRC_H */
