CC=gcc
CFLAGS=-I.
DEPS =
CLIENT_OBJ = test-client.o  
SERVER_OBJ = test-server.o

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
	rm -f *.o
