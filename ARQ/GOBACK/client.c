#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[100];
    int ack_received = -1;

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

    int next_frame = 0;

    while (ack_received < TOTAL_FRAMES - 1) {
        // Send window of frames
        for (int i = next_frame; i < next_frame + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            sprintf(message, "Frame %d", i);
            send(sock, message, strlen(message), 0);
            printf("Sent: %s\n", message);
        }

        // Receive ACK
        int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        buffer[bytes] = '\0';
        int ack;
        sscanf(buffer, "ACK %d", &ack);
        printf("Received: %s\n\n", buffer);

        if (ack == ack_received + WINDOW_SIZE) {
            // No error, move window
            ack_received = ack;
            next_frame = ack_received + 1;
        } else {
            // Error detected, go back
            printf("Go-Back-N: Resending from frame %d\n\n", ack + 1);
            next_frame = ack + 1;
            ack_received = ack;
        }
    }

    printf("All frames sent successfully!\n");

    close(sock);
    return 0;
}
