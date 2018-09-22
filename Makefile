VPATH = ./tcp:./nio

all : tcpserv tcpclient nioserv nioclient
.PHONY : all

# 变量
#Search Path for All Prerequisites

serv_objects=tcpserv.o signal.o sigchldwait.o
client_objects=tcpclient.o read.o


nioserv : nioserv.o
	cc -o nioserv nioserv.o

nioclient : nioclient.o read.o
	cc -o nioclient nioclient.o read.o


tcpserv :  $(serv_objects)
	cc -o tcpserv $(serv_objects)

tcpclient: $(client_objects)
	cc -o tcpclient $(client_objects)

tcpclient.o: tcpclient.c tcp.h
	cc -c $<

#Directory Searches are Performed
#Writing Recipes with Directory Search
#  ‘$^’ : a list of all the prerequisites of the rule, including the names of the directories in which they were found
#  ‘$@’ : the target
#  ‘$<’ : just the first prerequisite

nioserv.o: nioserv.c tcp.h
	cc -c $(CFLAGS) $<

nioclient.o:  nioclient.c tcp.h read.h
	cc -c $(CFLAGS) $<

tcpserv.o: tcpserv.c tcp.h
	cc -c $(CFLAGS) $<

read.o: read.c read.h
	cc -c $<

signal.o: signal.c tcp.h
	cc -c $<

sigchldwait.o: sigchldwait.c tcp.h
	cc -c $<
clean :
	rm tcpserv tcpclient nioserv nioclient nioserv.o  nioclient.o $(serv_objects) $(client_objects)
