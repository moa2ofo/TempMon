#include "TempMon_Run.h"
#include "TempMon_priv.h"

TempMon_sts_e Sts_e = TEMPMON_STS_NORMAL;

/* FUNCTION TO TEST */

void TempMon_Run(int32_t temp_mC)
{
    switch (Sts_e)
    {
        case TEMPMON_STS_NORMAL:
        default:
        {
            if (IsUnderEnter_b(temp_mC) == true)
            {
                Sts_e = TEMPMON_STS_UNDER;
            }
            else if (IsOverEnter_b(temp_mC) == true)
            {
                Sts_e = TEMPMON_STS_OVER;
            }
            else
            {
                /* stay NORMAL */
            }
            break;
        }

        case TEMPMON_STS_UNDER:
        {
            if (IsUnderExit_b(temp_mC) == true)
            {
                Sts_e = TEMPMON_STS_NORMAL;
            }
            else
            {
                /* stay UNDER */
            }
            break;
        }

        case TEMPMON_STS_OVER:
        {
            if (IsOverExit_b(temp_mC) == true)
            {
                Sts_e = TEMPMON_STS_NORMAL;
            }
            else
            {
                /* stay OVER */
            }
            break;
        }
    }
}