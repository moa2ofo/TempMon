#ifndef TEST_TEMPMON_ISOVERALV_B_H
#define TEST_TEMPMON_ISOVERALV_B_H

#include "TempMon.h"

/**
 * @brief Convenience check: returns true if status is TEMPMON_STS_OVER.
 *
 * @details
 * **Goal of the function**
 *
 * Provide a boolean helper to quickly check whether the
 * TEMPMON_STS_OVER-temperature condition is currently active.
 *
 * The processing logic:
 * - Compares internal state to #TEMPMON_STS_OVER.
 * - Returns true if equal, otherwise false.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range    | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|---------------|----------|
 * | Sts_e                   | X  |  X  | bool                   |   -   | - |
 * - |         - | {false, true} | [-]      |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (Sts_e == TEMPMON_STS_OVER) then (yes)
 *   :return true;
 * else (no)
 *   :return false;
 * endif
 * stop
 * @enduml
 *
 * @return
 * true if TEMPMON_STS_OVER-temperature is active, false otherwise.
 */
_Bool TempMon_IsOverAlv_b(void);

TempMon_sts_e get_Sts_e(void);
void set_Sts_e(TempMon_sts_e val);

#endif /* TEST_TEMPMON_ISOVERALV_B_H */
