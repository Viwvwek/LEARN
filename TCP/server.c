#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main() {
    int sock,new_socket;
    struct sockaddr_in address;
    int address_len  = sizeof(address); 
    
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
    bind(sock,(struct sockaddr*)&address,sizeof(address));
    if(bind<0)
    {
        printf("binding has failed\n");
        
    } 
    printf("bind successfull\n");

    //listen
    if(listen(sock, 3)<0)
    {
        printf("Listening has failed\n");
        return -1;
    }
    printf("Listening on port %d\n",PORT);


    new_socket = accept(sock,(struct sockaddr*)&address, (socklen_t*)&address_len);
    if(new_socket<0)
    {
        printf("Socket acception failed\n");
        return -1;
    }
    printf("Accpeted\n");


    recv(new_socket,buffer,sizeof(buffer),0);
    printf("The received message from the Client is:%s", buffer);

    // send the message
    printf("Enter the message to the client: ");
    fgets(buffer,sizeof(buffer),stdin);
    send(sock,buffer, strlen(buffer),0);

    //close the socket
    close(new_socket);
    close(sock);
}