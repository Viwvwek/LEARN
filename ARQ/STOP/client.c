#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define TOTAL_FRAMES 5

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    for (int frame = 0; frame < TOTAL_FRAMES; frame++) {
        sprintf(message, "Frame %d", frame);
        send(sock, message, strlen(message), 0);
        printf("Sent: %s\n", message);

        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        buffer[bytes] = '\0';
        printf("Received: %s\n", buffer);
    }

    printf("All frames sent successfully!\n");

    close(sock);
    return 0;
}
