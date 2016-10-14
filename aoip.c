#include "aoip.h"


 void init_addr(struct sockaddr_in *server_addr, in_addr_t address, int port) {
  // Zero memory for initialization
  bzero(server_addr, sizeof(*server_addr));

  // Set properties for address
  server_addr->sin_family      = AF_INET;
  server_addr->sin_addr.s_addr = address;
  server_addr->sin_port        = htons(port);
}


int init_socket(struct sockaddr *server_addr, size_t addr_len) {
  // Create socket
  int sock_id = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_id < 0) return -1;

  // Bind socket
  int bound = bind(sock_id, server_addr, addr_len);
  if (bound < 0) return -2;

  // Return socket file descriptor
  return sock_id;
}
