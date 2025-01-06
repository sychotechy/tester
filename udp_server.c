#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server;
    char servMsg[2000], cliMsg[2000];
    struct sockaddr_in servAddr, client_addr;
    int client_struct_length = sizeof(client_addr);

    // Create socket
    server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server < 0) {
        perror("Error while creating socket");
        exit(1);
    }
    printf("Socket created successfully\n");

    // Set socket options to allow address reuse
    int optval = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("Error setting socket options");
        close(server);
        exit(1);
    }

    // Prepare server address
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2002);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Print the address and port we are trying to bind to
    printf("Trying to bind to 127.0.0.1:2002\n");

    // Bind the socket to the port
    if (bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Couldn't bind to the port");
        close(server);
        exit(1);
    }
    printf("Binding done\n");

    // Server is ready to listen
    printf("Listening...\n");

    // Receive message from client
    if (recvfrom(server, cliMsg, sizeof(cliMsg), 0, (struct sockaddr*)&client_addr, &client_struct_length) < 0) {
        perror("Couldn't receive");
        close(server);
        exit(1);
    }

    // Print message from client
    printf("Msg from client: %s\n", cliMsg);

    // Copy message to server's response and send it back to client
    strcpy(servMsg, cliMsg);
    if (sendto(server, servMsg, strlen(servMsg), 0, (struct sockaddr*)&client_addr, client_struct_length) < 0) {
        perror("Can't send");
        close(server);
        exit(1);
    }

    // Close the socket
    close(server);
    return 0;
}

