#include <stdio.h>
#include <ctype.h>             /* Req'd for isdigit() fn       */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */

/* Function: IsBufNumeric()
 * Description:
 *   Checks if the buffer with given length is numeric or not.
 *   if success returns RC_SUCCESS(0) else returns RC_FAILURE(1).
 */
int IsBufNumeric (char *bufPtr, int bufLen)
{
    int count = 0;

    if ((bufPtr == NULL) || (bufLen <= 0))
        return RC_FAILURE;

    for (count = 0; count < bufLen; count++)
    {
        if (isdigit (*(bufPtr + count)) == 0)
            break;
    }

    if (count == bufLen)
        return RC_SUCCESS;
    else
        return RC_FAILURE;

} /* End of IsBufNumeric() */

/* End of IsBufNumeric.c */
