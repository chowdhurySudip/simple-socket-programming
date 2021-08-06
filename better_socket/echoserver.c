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

#define TRUE 1
#define MSGSIZE 16
#define LOCALHOST "127.0.0.1"

int main(int argc, char **argv) {
  int portno = 25246;  /* port to listen on */
  int maxnpending = 5;

  struct addrinfo my_server, *all_addrs, *p;
  int status;
  char *host = LOCALHOST;
  char port[6], message[MSGSIZE];
  int server_sock, client_sock;
  int yes = 1;

  memset(&my_server, 0, sizeof(my_server));
  my_server.ai_family = AF_INET;
  my_server.ai_socktype = SOCK_STREAM;

  sprintf(port, "%d", portno);

  if((status=getaddrinfo(host, port, &my_server, &all_addrs)) != 0){
    fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(status));
    exit(1);
  }
  
  for(p=all_addrs; p!=NULL; p=p->ai_next){
    if((server_sock=socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      fprintf(stderr, "Error in socket");
      continue;
    }

    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      fprintf(stderr, "Error in setsockopt");
      exit(1);
    }

    if(bind(server_sock, p->ai_addr, p->ai_addrlen) == -1){
      close(server_sock);
      fprintf(stderr, "Error in bind");
      continue;
    }

    break;
  }

  freeaddrinfo(all_addrs);

  if(p==NULL){
    fprintf(stderr, "Server failed to bind");
    exit(1);
  }

  if(listen(server_sock, maxnpending) == -1){
    fprintf(stderr, "Failed in listen");
    exit(1);
  }

  while (TRUE){
    client_sock = accept(server_sock, NULL, NULL);
    if(client_sock==-1){
      fprintf(stderr, "Failed in accept");
      exit(1);
    }

    if(recv(client_sock, message, MSGSIZE-1, 0) == -1){
      fprintf(stderr, "Failed at recieve");
      exit(1);
    }

    send(client_sock, message, sizeof(message), 0);

    close(client_sock);
  }
  
  close(server_sock);

  return 0;
}
