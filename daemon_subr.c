#include "daemon_subr.h"


int daemonized(void)
{
    int fd;
    printf("daemonizing");
    if ((fd = open(_PATH_TTY, O_RDONLY | O_NOCTTY)) >= 0)
    {
        close(fd);
        return 0;   /* have controlling terminal */
    }
    if (getppid() != 1)
        return 0;   /* started by init */
    if (getsid(0) != getpid())
        return 0;   /* not session leader */
    printf("already daemonized\n");
    return 1;
}

void disconnect_controlling_tty(void)
{
    int fd;
    if ((fd = open(_PATH_TTY, O_RDWR | O_NOCTTY)) >= 0) {
        (void) ioctl(fd, TIOCNOTTY, NULL);
        close(fd);
    }
}

int create_pidfile()
{
    int fp;
    int pid;
    pid = getpid();
    if((fp = open(PIDPATH, O_WRONLY | O_CREAT)) < 0)
        return errno;
    dprintf(fp, "%d\n", pid);
    close(fp);
    return 0;
}
