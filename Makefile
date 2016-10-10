CC = gcc

all: librtp server client

librtp: rtp.c
	$(CC) -c -o librtp.a rtp.c

server: server.c
	$(CC) -o server server.c -L. -lportaudio -lrtp

client: client.c
	$(CC) -o client client.c -L. -lportaudio -lrtp

clean:
	rm -f server.o server
	rm -f client.o client
