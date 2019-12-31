#include <stdio.h>
#include <stdlib.h>            /* Req'd for atoi() fn          */
#include <string.h>            /* Req'd for strlen() fn        */
#include <unistd.h>            /* Req'd for read() fn        */
#include <sys/socket.h>        /* Req'd for socket fn's        */
#include <sys/un.h>            /* Req'd for sockaddr_un struct */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */
#include "ksockqueue.h"        /* Req'd for KSOCK macros       */

int main (int argc, char *argv[])
{
    int funcRc = 0;
    int queueNo = 0;
    int thisQFd = 0;
    int cliFd = 0;
    struct sockaddr_un thisQAddr = {0};
    char socket_path[KSOCK_NAME_MAX_SZ + 1] = {0};
    char rcvBuf[KSOCK_MSG_MAX_SZ] = {0};

    (void) fprintf (stdout, "PG_KSOCK01 - argc: %d, argv: %p\n",
                    argc, argv);

    if (--argc != 1)
    {
        (void) fprintf (stderr, "PG_KSOCK01 - Only 1 arg is required\n");
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

    queueNo = atoi (argv[1]);

    if ((thisQFd = socket (AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror ("socket() failed");
        exit RC_ERROR;
    }

    thisQAddr.sun_family = AF_UNIX;
    (void) snprintf (socket_path, sizeof(socket_path), "%s%.2d",
                     KSOCK_NAME_PREFIX, queueNo);
    (void) memcpy (thisQAddr.sun_path, socket_path, sizeof(socket_path));

    unlink (socket_path);
    if ((funcRc = bind (thisQFd, (struct sockaddr *) &thisQAddr,
                        sizeof(thisQAddr))) == -1)
    {
        perror ("bind() failed");
        exit RC_ERROR;
    }

    if ((funcRc = listen (thisQFd, 5)) == -1)
    {
        perror ("listen() failed");
        exit RC_ERROR;
    }

    while (1)
    {
        if ((cliFd = accept (thisQFd, NULL, NULL)) == -1)
        {
            perror ("accept() failed");
            continue;
        }

        (void) memset (rcvBuf, 0x00, sizeof(rcvBuf));
        funcRc = read (cliFd, rcvBuf, sizeof(rcvBuf));
        if (funcRc == -1)
        {
            perror ("read() failed");
            exit RC_ERROR;
        }
        else if (funcRc == 0)
        {
            close (cliFd);
        }

        funcRc = SndMsg2NxtQ (5, rcvBuf, strlen(rcvBuf));
        if (funcRc != RC_SUCCESS)
        {
            (void) fprintf (stderr, "PG_KSOCK01 - SndMsg2NxtQ() failed with "
                            "rc: %d\n", funcRc);
            return RC_FAILURE;
        }
    }

    (void) fprintf (stdout, "PG_KSOCK01 - exited successfully\n");
    return RC_SUCCESS;
} /* End of main() */

/* End of PG_KSOCK01.c */
