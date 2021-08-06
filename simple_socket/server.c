#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TRUE 1

int main(){
    int server_socket, client_socket;
    char buffer[256];
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

    listen(server_socket, 5);

    while (TRUE){
        client_socket = accept(server_socket, NULL, NULL);

        recv(client_socket, &buffer, sizeof(buffer), 0);

        send(client_socket, buffer, sizeof(buffer), 0);

        close(client_socket);
    }
    
    close(server_socket);

    return 0;
}