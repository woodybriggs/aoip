#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 8600
#endif

struct sockets {
  int    file_des[];
  void * data_buffer[];
}

typedef struct {
  double timestamp;
} aoip_header;

typedef struct {
  aoip_header header;
  void * payload;
} aoip_packet;

// Socket Stuff
void init_addr(struct sockaddr_in * server_addr, in_addr_t address, int port);
int  init_socket(struct sockaddr * server_addr, size_t addr_len);
