#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main() {
    int sock;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    // create the socket 
    

    // Create socket
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("Socket creation ha failed\n");
        return -1;

    }
    printf("Socket creation success fully\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    
    // bind
    connect(sock,(struct sockaddr*)&address, sizeof(address));
    if(bind<0)
    {
        printf("binding has failed\n");
        return -1;
    } 
    printf("connect successfull\n");

    //SEND
    printf("Enter the message for the Server: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(sock,buffer, strlen(buffer),0);


    recv(sock, buffer, sizeof(buffer),0);
    printf("Message from the Server is:%s",buffer);




    

}