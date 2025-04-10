// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Socket creation failed");
        return -1;
    }
    printf("Socket created successfully\n");

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if(bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return -1;
    }
    printf("Server listening on port %d...\n", PORT);

    // Receive message from client
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
    printf("Message from client: %s\n", buffer);

    memset(buffer,0,sizeof(buffer));
    printf("enter the message to the client\n");
    fgets(buffer,sizeof(buffer),stdin);

    sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr, addr_len);
    close(sock);
    return 0;
}
