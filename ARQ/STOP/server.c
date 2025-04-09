#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024];
    int addrlen = sizeof(address);
    int frame_no;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted!\n");

    while (1) {
        int bytes = recv(new_socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            printf("Connection closed by client.\n");
            break;
        }
 
        buffer[bytes] = '\0';
        sscanf(buffer, "Frame %d", &frame_no);
        printf("Received: %s\n", buffer);

        // Send ACK
        sprintf(buffer, "ACK %d", frame_no);
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Sent: %s\n", buffer);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
