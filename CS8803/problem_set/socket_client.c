#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define HOST "localhost"
#define PORT 8080

int main(int argc, char **argv) {
  int socket_fd = 0;
  struct sockaddr_in server_socket_addr;

  struct hostent *he = gethostbyname(HOST);
  unsigned long server_addr_nbo = *(unsigned long *)(he->h_addr_list[0]);

  if (0 > (socket_fd = socket(AF_INET, SOCK_STREAM, 0))) {
    printf("client failed to create socket connection\n");
    exit(1);
  }

  bzero(&server_socket_addr, sizeof(server_socket_addr));
  server_socket_addr.sin_family = AF_INET;
  server_socket_addr.sin_port = htons(PORT);
  server_socket_addr.sin_addr.s_addr = server_addr_nbo;

  if (0 > connect(socket_fd, (struct sockaddr *)&server_socket_addr, sizeof(server_socket_addr))) {
    printf("client failed to connect to %s:%d\n", HOST, PORT);
    exit(1);
  }

  printf("client connected to %s:%d\n", HOST, PORT);
  close(socket_fd);
  return 0;
}