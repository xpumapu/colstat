CC=gcc
CFLAGS=-I.
DEPS = debug.h
CLIENT_OBJ = test-client.o debug.o 
SERVER_OBJ = test-server.o debug.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all

all: test-client test-server

test-client: $(CLIENT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test-server: $(SERVER_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o test-client test-server
