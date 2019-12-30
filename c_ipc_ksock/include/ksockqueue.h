#ifndef KSOCKQUEUE_H
#define KSOCKQUEUE_H

/* Macros for KSOCK functions */
#define KSOCK_NAME_PREFIX     "KSOCK"
#define KSOCK_NAME_MAX_SZ     7
#define KSOCK_MSG_MAX_SZ      255

/* Function Prototypes for KSOCK functions */
int SndMsg2NxtQ (int queueNo, char *msgPtr, int msgLen);

#endif /* KSOCKQUEUE_H */

/* End of ksockqueue.h */
