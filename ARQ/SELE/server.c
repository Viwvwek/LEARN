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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1000];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        printf("Socket creation failed\n");
        return -1;
    }
    printf("Socket created successfully\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("Bind failed\n");
        return -1;
    }
    printf("Bind successful\n");

    listen(server_fd, 3);
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    printf("Connection accepted\n");

    int expected_frame = 0;
    while (expected_frame < TOTAL_FRAMES) {
        for (int i = 0; i < WINDOW_SIZE && expected_frame + i < TOTAL_FRAMES; i++) {
            int bytes = recv(new_socket, buffer, sizeof(buffer), 0);
            printf("Received: %s\n", buffer);

            // Simulate random success or error
            int success = rand() % 2;

            if (success) {
                printf("Frame %d received correctly. Sending ACK.\n", expected_frame);
                sprintf(buffer, "ACK %d", expected_frame);
                send(new_socket, buffer, strlen(buffer), 0);
                expected_frame++;
            } else {
                printf("Frame %d received with error. Sending NACK.\n", expected_frame);
                sprintf(buffer, "ACK %d", expected_frame);
                send(new_socket, buffer, strlen(buffer), 0);
                break;
            }
        }
    }

    printf("All frames received successfully!\n");
    close(new_socket);
    close(server_fd);
    return 0;
}
