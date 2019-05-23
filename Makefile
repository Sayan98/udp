.PHONY: all

all: server client

server: server.c
	$(CC) server.c -o server.a

client: client.c
	$(CC) client.c -o client.a

clean:
	rm *.a
