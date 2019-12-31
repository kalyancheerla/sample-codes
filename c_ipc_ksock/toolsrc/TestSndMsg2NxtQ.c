#include <stdio.h>
#include <string.h>            /* Req'd for strlen() fn        */
#include <stdlib.h>            /* Req'd for atoi() fn          */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */
#include "ksockqueue.h"        /* Req'd for SndMsg2NxtQ() fn   */

int main (int argc, char *argv[])
{
    int funcRc = 0;

    (void) fprintf (stdout, "TestSndMsg2NxtQ - argc: %d, argv: %p\n",
                    argc, argv);

    if (--argc != 2)
    {
        (void) fprintf (stderr, "TestSndMsg2NxtQ - Only 2 arg's is required\n");
        return RC_FAILURE;
    }

    funcRc = IsBufNumeric (argv[1], strlen(argv[1]));
    if (funcRc != RC_SUCCESS)
    {
        (void) fprintf (stderr, "TestSndMsg2NxtQ - IsBufNumeric() failed with "
                        "rc: %d\n", funcRc);
        (void) fprintf (stderr, "TestSndMsg2NxtQ - 1st arg is number\n");
        return RC_FAILURE;
    }

    funcRc = SndMsg2NxtQ (atoi(argv[1]), argv[2], strlen(argv[2]));
    if (funcRc != RC_SUCCESS)
    {
        (void) fprintf (stderr, "TestSndMsg2NxtQ - SndMsg2NxtQ() failed with "
                        "rc: %d\n", funcRc);
        return RC_FAILURE;
    }

    (void) fprintf (stdout, "TestSndMsg2NxtQ - exited successfully\n");
    return RC_SUCCESS;
} /* End of main() */

/* End of TestSndMsg2NxtQ.c */
