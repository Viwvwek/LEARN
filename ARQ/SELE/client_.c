#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080 
#define TOTAL_FRAMES 5
#define WINDOW_SIZE 3

int main() {
    int sock_fd;
    struct sockaddr_in address;
    char buffer[1000];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        printf("Socket creation failed\n");
        return -1;
    }
    printf("Socket created successfully\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    printf("Connected successfully\n");

    int base = 0;
    int ack;
    char message[100];

    while (base < TOTAL_FRAMES)
    {
        // Send frames in window
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            sprintf(message, "Frame %d", i);
            send(sock_fd, message, strlen(message), 0);
            printf("Sent: %s\n", message);
        }

        // Receive ACKs
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            int bytes = recv(sock_fd, buffer, sizeof(buffer), 0);
            sscanf(buffer, "ACK %d", &ack);

            if (ack == i) {
                printf("Received ACK: %d\n", ack);
                base++;
            } else {
                printf("NACK for Frame %d, resending from Frame %d\n", i, ack);
                base = ack;
                break;
            }
        }
    }

    printf("All frames sent successfully!\n");
    close(sock_fd);
    return 0;
}
