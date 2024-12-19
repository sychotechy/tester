#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main(){
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;

    client = socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
    printf("1. Sending data to server....\n");

    strcpy(buffer, "Hi, This is client\n");
    send(client,buffer,19,0);
    printf("2. Receiving data from server....\n");
    recv(client,buffer,1024,0);
    printf("Server says: %s\n",buffer);
    close(client);
}