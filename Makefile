OBJ = laudio_daemon.o \
	  daemon_subr.o
INC = .
CC = gcc
CLFAGS= -g

daemon : ${OBJ}
	${CC} ${CFLAGS} -o saud ${OBJ}

%.o : %.c ${HEADERS}
	${CC} ${CFLAGS} -I ${INC} -c $< -o $@

install:
	cp saud /usr/sbin/saud
	cp rcscript /etc/rc.d/saud

clean:
	rm -f saud *.o
