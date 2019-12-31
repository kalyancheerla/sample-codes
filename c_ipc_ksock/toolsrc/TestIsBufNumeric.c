#include <stdio.h>
#include <string.h>            /* Req'd for strlen() fn        */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */

int main (int argc, char *argv[])
{
    int funcRc = 0;

    (void) fprintf (stdout, "TestIsBufNumeric - argc: %d, argv: %p\n",
                    argc, argv);

    if (--argc != 1)
    {
        (void) fprintf (stderr, "TestIsBufNumeric - Only 1 arg is required\n");
        return RC_FAILURE;
    }

    funcRc = IsBufNumeric (argv[1], strlen(argv[1]));
    if (funcRc != RC_SUCCESS)
    {
        (void) fprintf (stderr, "TestIsBufNumeric - IsBufNumeric() failed with "
                        "rc: %d\n", funcRc);
        return RC_FAILURE;
    }

    (void) fprintf (stdout, "TestIsBufNumeric - exited successfully\n");
    return RC_SUCCESS;
} /* End of main() */

/* End of TestIsBufNumeric.c */
