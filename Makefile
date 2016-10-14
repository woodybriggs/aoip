CC = gcc

all: libaoip server client

libaoip: aoip.c
	$(CC) -c -o libaoip.a aoip.c

server: server.c
	$(CC) -o server server.c -L. -lportaudio -laoip

client: client.c
	$(CC) -o client client.c -L. -lportaudio -laoip

clean:
	rm -f server.o server
	rm -f client.o client
