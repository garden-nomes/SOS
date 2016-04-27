SERVER_EXE=barrier
CLIENT_EXE=client
CC=gcc
COPTS=

all: server client

server: barrier.c
	$(CC) $(COPTS) -o $(SERVER_EXE) barrier.c

client: testclient.c
	$(CC) $(COPTS) -o $(CLIENT_EXE) testclient.c waitatbarrier.c

clean:
	rm -rf *.o $(SERVER_EXE) $(CLIENT_EXE)
