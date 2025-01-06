#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int server,newSock;
    char buffer[1024];
    struct sockaddr_in serverAddress;
    struct sockaddr_storage store;
    socklen_t addrSize;
    server = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6265);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.01");
    bind(server,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
    if(listen(server,5)==0){
        printf("Server is listening...\n");
    }
    else{
        printf("Error in listening...\n");
    }
    newSock = accept(server,(struct sockaddr*)&store,&addrSize);
    recv(newSock,buffer,1024,0);
    printf("Client message: %s\n",buffer);
    strcpy(buffer,"Hi this is server\n");
    printf("Sending data to client....\n");
    send(newSock,buffer,19,0);
    close(newSock);
    close(server);
}