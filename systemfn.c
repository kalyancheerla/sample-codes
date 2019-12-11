#include <stdio.h>

#define CMD_MAX_SZ 255

int main (int argc, char *argv[])
{
    int rc = 0;
    char cmd_buffer[CMD_MAX_SZ] = {0};
    if (--argc != 1)
        return 2;
    snprintf (cmd_buffer, sizeof(cmd_buffer), "%s 2>&1", argv[1]);
    rc = system(cmd_buffer);
    printf ("rc = %d\n", rc);
    return 0;
}
