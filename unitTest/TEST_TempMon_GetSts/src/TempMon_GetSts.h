#ifndef TEST_TEMPMON_GETSTS_H
#define TEST_TEMPMON_GETSTS_H

#include "TempMon.h"
#include "TempMon_priv.h"

/**
 * @brief Get the current status of the temperature monitor.
 *
 * @details
 * **Goal of the function**
 *
 * Provide read access to the internal state machine status updated by
 * TempMon_Init() and TempMon_Run().
 *
 * The processing logic:
 * - Returns the current internal state value.
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Data type / Signature | Param | Data
 * factor | Data offset | Data size | Data range | Data unit |
 * |-------------------------|:--:|:---:|------------------------|:-----:|------------:|------------:|----------:|----------------------------------------------|----------|
 * | Sts_e | X  |  X  | TempMon_sts_e          |   -   |           - | - | - |
 * TEMPMON_STS_NORMAL / TEMPMON_STS_UNDER / OVER | [-]      |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :return Sts_e;
 * stop
 * @enduml
 *
 * @return
 * Current temperature monitor status (#TempMon_sts_e).
 */
TempMon_sts_e TempMon_GetSts(void);

TempMon_sts_e get_Sts_e(void);
void set_Sts_e(TempMon_sts_e val);

#endif /* TEST_TEMPMON_GETSTS_H */
