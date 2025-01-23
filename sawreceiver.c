#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int ack_prob = 70;

    srand(time(0));

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server: Waiting for connection...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Server: Connection established.\n");

    while (1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread == 0) break;

        printf("Server: Received packet - %s\n", buffer);

        if (rand() % 100 < ack_prob) {
            printf("Server: ACK sent for packet %s\n\n", buffer);
            send(new_socket, "ACK", strlen("ACK"), 0);
        } else {
            printf("Server: ACK lost for packet %s\n\n", buffer);
        }

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}