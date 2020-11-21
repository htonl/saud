#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include "daemon_subr.h"

int main(int argc, char **argv)
{
    int dont_daemonize = 0;
    int local_play = 0;
    int  web_play = 0;
    int c;
    int rc;
    char *host = NULL;
    //arg parse
    while ((c = getopt (argc, argv, "dlw:")) != -1)
        switch (c)
        {
            case 'd':
                dont_daemonize = 1;
                break;
            case 'l':
                local_play = 1;
                break;
            case 'w':
                web_play = 1;
                host = optarg;
                break;
            case '?':
                if (optopt == 'w')
                    fprintf(stderr, "Option -%c requires an argument.\n",
                            optarg);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character \\x%x.\n",
                            optopt);
                return 1;
            default:
                abort();
        }
    printf("dont_daemonize = %d, local_play = %d, web_play = %d, host = %s\n",
            dont_daemonize, local_play, web_play, host);
    if (!daemonized())
    {
        printf("daemonizing");
        if (daemon(0, 0) == -1)
        {
            printf("daemon() failed %s", strerror(errno));
            return -1;
        }
        disconnect_controlling_tty();
    }
    // be a good little daemon
    if((rc = create_pidfile()) != 0)
    {
        printf("error creating pid%d\n", rc);
        return rc;
    }
    // Run
    while (1) {
        sleep(10);
        printf("nice sleep\n");
    }
    return 0;
}
