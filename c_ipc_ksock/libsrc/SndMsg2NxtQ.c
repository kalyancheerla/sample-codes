#include <stdio.h>
#include <stdlib.h>            /* Req'd for exit() fn          */
#include <string.h>            /* Req'd for memcpy() fn        */
#include <unistd.h>            /* Req'd for write() fn         */
#include <sys/socket.h>        /* Req'd for socket fn's        */
#include <sys/un.h>            /* Req'd for sockaddr_un struct */

/* USER DEFINED HEADERS */
#include "kcompiler.h"         /* Req'd for return codes       */
#include "ksockqueue.h"        /* Req'd for KSOCK macros       */

/* Function: SndMsg2NxtQ()
 * Description:
 *   Connects to a UNIX Domain Socket (KSOCK??) of the Next
 *   Queue and Sends the message (len - >0 & <255) to the
 *   Next Queue (?? - represents Queue Number).
 *   if success returns RC_SUCCESS(0) else RC_FAILURE(1).
 *   if any important functions fail then exits with RC_ERROR(-1).
 */
int SndMsg2NxtQ (int queueNo, char *msgPtr, int msgLen)
{
    int funcRc = 0;
    int nxtQFd = 0;
    struct sockaddr_un nxtQAddr = {0};
    char socket_path[KSOCK_NAME_MAX_SZ + 1] = {0};

    (void) fprintf (stdout, "SndMsg2NxtQ() - queueNo: %d, msgPtr: %p "
                    "msgLen: %d\n", queueNo, msgPtr, msgLen);

    if ((msgPtr == NULL) && (msgLen < 0) && (msgLen > KSOCK_MSG_MAX_SZ))
    {
        (void) fprintf (stderr, "SndMsg2NxtQ() - Invaild Input Args\n");
        return RC_FAILURE;
    }

    if ((nxtQFd = socket (AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror ("socket() failed");
        exit RC_ERROR;
    }

    nxtQAddr.sun_family = AF_UNIX;
    (void) snprintf (socket_path, sizeof(socket_path), "%s%.2d",
                     KSOCK_NAME_PREFIX, queueNo);
    (void) memcpy (nxtQAddr.sun_path, socket_path, sizeof(socket_path));

    if ((funcRc = connect (nxtQFd, (struct sockaddr *) &nxtQAddr,
                           sizeof(nxtQAddr))) == -1)
    {
        perror ("connect() failed");
        exit RC_ERROR;
    }

    funcRc = write (nxtQFd, msgPtr, msgLen);
    if (funcRc != msgLen)
    {
        if (funcRc > 0)
        {
            (void) fprintf (stderr, "write() function wrote partially with "
                            "rc: %d\n", funcRc);
            return RC_FAILURE;
        }
        else
        {
            perror ("write() failed");
            exit RC_ERROR;
        }
    }

    (void) fprintf (stdout, "SndMsg2NxtQ() - exited successfully\n");
    return RC_SUCCESS;
} /* End of SndMsg2NxtQ() */

/* End of SndMsg2NxtQ.c */
