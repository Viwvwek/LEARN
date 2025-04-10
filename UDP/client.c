// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Socket creation failed");
        return -1;
    }
    printf("Socket created successfully\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Get message from user
    printf("Enter the message for the Server: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send message to server
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &addr_len);

    printf("Message from client: %s\n", buffer);
    close(sock);
    return 0;
}
