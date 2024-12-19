#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 6265

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == 0) {
        printf("Server listening on port %d\n", PORT);
    } else {
        perror("Listen failed");
        exit(1);
    }

    // Accept connection from the client
    addr_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    if (client_fd < 0) {
        perror("Accept failed");
        exit(1);
    }

    // Receive data from the client
    recv(client_fd, buffer, 1024, 0);
    printf("Client says: %s\n", buffer);

    // Send a response back to the client
    strcpy(buffer, "Hello from server");
    send(client_fd, buffer, strlen(buffer), 0);
    printf("Server response sent.\n");

    // Close the sockets
    close(client_fd);
    close(server_fd);

    return 0;
}
