all : tcpserv tcpclient
.PHONY : all

tcpserv :  tcpserv.o signal.o sigchldwait.o
	cc -o tcpserv tcpserv.o signal.o sigchldwait.o

tcpclient: tcpclient.o read.o
	cc -o tcpclient tcpclient.o read.o

tcpclient.o: tcpclient.c tcp.h
	cc -c tcpclient.c

tcpserv.o: tcpserv.c tcp.h
	cc -c tcpserv.c

read.o: read.c read.h
	cc -c read.c

signal.o: signal.c tcp.h
	cc -c signal.c

sigchldwait.o: sigchldwait.c tcp.h
	cc -c sigchldwait.c
clean :
	rm tcpserv.o signal.o sigchldwait.o /
	tcpclient.o read.o
