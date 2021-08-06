#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main (){
    int client_socket, connection;
    char buffer[256], *old_message = "Sudip Chowdhury";
    struct sockaddr_in server_addr;

    char message[256];

    strcpy(message, old_message);

    printf("To send: %s\n", message);
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connection = connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if(connection == -1){
        printf("Error making a connection\n");
    }

    send(client_socket, message, sizeof(message), 0);

    recv(client_socket, &buffer, sizeof(buffer), 0);

    fprintf(stdout, "%s", buffer);

    close(client_socket);

    return 0;
}