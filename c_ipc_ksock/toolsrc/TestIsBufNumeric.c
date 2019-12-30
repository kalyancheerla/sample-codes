#include <stdio.h>
#include <string.h>            /* Req'd for strlen() fn        */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */

int main (int argc, char *argv[])
{
    int funcRc = 0;

    (void) fprintf (stdout, "verifyNum - argc: %d, argv: %p\n", argc, argv);

    if (--argc != 1)
    {
        (void) fprintf (stderr, "verifyNum - Only 1 arg is required\n");
        return RC_FAILURE;
    }

    funcRc = IsBufNumeric (argv[1], strlen(argv[1]));
    if (funcRc != RC_SUCCESS)
    {
        (void) fprintf (stderr, "verifyNum - IsBufNumeric() failed with "
                        "rc: %d\n", funcRc);
        return RC_FAILURE;
    }

    (void) fprintf (stdout, "verifyNum - exited successfully\n");
    return RC_SUCCESS;
}
