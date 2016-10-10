#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

// Socket Stuff
void init_addr(struct sockaddr_in *server_addr, in_addr_t address, int port);
int  init_socket(struct sockaddr *server_addr, size_t addr_len);
