#include <stdio.h>

#define CMD_MAX_SZ 255

int main (int argc, char *argv[])
{
    char cmd_buffer[CMD_MAX_SZ] = {0};
    FILE *fp = NULL;

    if (--argc != 1)
        return 1;
    snprintf (cmd_buffer, sizeof(cmd_buffer), "%s 2>&1", argv[1]);
    if ((fp = popen (cmd_buffer, "r")) == NULL)
    {
        fprintf (stderr, "Unable to open pipe\n");
        return 2;
    }
    else
    {
        while (1)
        {
            if ((fgets (cmd_buffer, CMD_MAX_SZ, fp)) == NULL)
            {
                break;
            }
            else
            {
                fprintf (stdout, "[+] %s", cmd_buffer);
            }
        }
    }
    return 0;
}
