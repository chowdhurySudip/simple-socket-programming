#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MSGSIZE 16
#define LOCALHOST "127.0.0.1"

int main(int argc, char **argv) {
  char *hostname = "localhost";
  unsigned short portno = 25246;
  char *message = "Hello World!!";

  struct addrinfo my_server, *all_addrs, *p;
  int status;
  char port[6], new_message[MSGSIZE], old_message[MSGSIZE];
  int client_socket;
  int rec;

  memset(&my_server, 0, sizeof(my_server));
  my_server.ai_family = AF_INET;
  my_server.ai_socktype = SOCK_STREAM;

  sprintf(port, "%d", portno);

  strcpy(old_message, message);

  if (strcmp(hostname,"localhost") == 0){
        hostname = LOCALHOST;
  }

  if((status=getaddrinfo(hostname, port, &my_server, &all_addrs)) != 0){
    fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(status));
    exit(1);
  }
  
  for(p=all_addrs; p!=NULL; p=p->ai_next){
    if((client_socket=socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      fprintf(stderr, "Error in socket");
      continue;
    }

    if(connect(client_socket, p->ai_addr, p->ai_addrlen) == -1){
      close(client_socket);
      fprintf(stderr, "Error in connect");
      continue;
    }

    break;
  }

  freeaddrinfo(all_addrs);

  if(p==NULL){
    fprintf(stderr, "Server failed to connect");
    exit(1);
  }

  send(client_socket, old_message, sizeof(old_message), 0);

  if((rec = recv(client_socket, new_message, MSGSIZE-1, 0)) == -1){
    fprintf(stderr, "Error in recv");
    exit(1);
  }

  printf("%s", new_message);

  close(client_socket);

  return 0;
}
