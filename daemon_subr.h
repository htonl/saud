#ifndef SERVCONF_H
#define SERVCONF_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>

#define PIDPATH "/var/run/saud.pid"
#define _PATH_TTY "/dev/tty"

int daemonized(void);
void disconnect_controlling_tty(void);
int create_pidfile(void);

#endif /* SERVCONF_H */
