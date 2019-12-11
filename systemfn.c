#include <stdio.h>
#include <stdlib.h>

#define CMD_MAX_SZ 255

int main (int argc, char *argv[])
{
    int rc = 0;
    char cmd_buffer[CMD_MAX_SZ] = {0};
    if (--argc != 1)
        return 1;
    snprintf (cmd_buffer, sizeof(cmd_buffer), "%s 2>&1", argv[1]);
    rc = system(cmd_buffer);
    // system() function return code is present in
    // upper 8 bits, so doing right shift
    printf ("rc = %d\n", rc>>8);
    return 0;
}
