#include <stdio.h>
#include <stdlib.h>
#include "rtp.h"

// Definitions
#ifndef RTP_PORT
#define RTP_PORT 8600
#endif

#ifndef RTCP_PORT
#define RTCP_PORT 8601
#endif

// Globals
int rtp_sock_fd;
struct sockaddr_in rtp_server_addr;


int main(int argc, char *argv[])
{
  // Socket Setup
  init_addr(&rtp_server_addr, INADDR_ANY, RTP_PORT);

  rtp_sock_fd  = init_socket((struct sockaddr *) &rtp_server_addr, sizeof(rtp_server_addr));
  if (rtp_sock_fd < 0) {
    perror("FAILED TO CREATE SOCKET");
    exit(1);
  }

  return 0;
}
