#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int client;
    struct sockaddr_in servAddr;
    char servMsg[2000], cliMsg[2000];
    int server_struct_length = sizeof(servAddr);

    // Create socket
    client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client < 0) {
        perror("Error while creating socket");
        exit(1);
    }
    printf("Socket created successfully\n");

    // Prepare server address
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2002);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Ask the user to enter a message
    printf("Enter message to server: ");
    fgets(cliMsg, sizeof(cliMsg), stdin);  // Safe input handling using fgets

    // Send message to server
    if (sendto(client, cliMsg, strlen(cliMsg), 0, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Unable to send message");
        close(client);
        exit(1);
    }

    // Receive message from server
    if (recvfrom(client, servMsg, sizeof(servMsg), 0, (struct sockaddr*)&servAddr, &server_struct_length) < 0) {
        perror("Error while receiving server's msg");
        close(client);
        exit(1);
    }

    printf("Received message from server: %s\n", servMsg);

    // Close socket
    close(client);
}

