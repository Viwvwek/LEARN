// server.c - Basic FTP Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define PORT 8080


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1000];

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(1);
    }

    // 2. Prepare sockaddr_in
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept from any interface
    address.sin_port = htons(PORT);

    // 3. Bind
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 4. Listen
    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    // 5. Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(1);
    }

    // 6. Receive filename
    recv(new_socket,buffer,sizeof(buffer),0);
    printf("Received filename: %s\n", buffer);

    FILE *fp = fopen(buffer, "rb");

    if(fp==NULL)
    {
        char * msg = "File not found";
        send(new_socket,msg,strlen(msg),0);
    }
    else
    {
        while(!feof(fp))
        {
            int in_bytes = fread(buffer,1,sizeof(buffer),fp);
            send(new_socket,buffer,sizeof(buffer),0);
        }
    }



    close(new_socket);
    close(server_fd);
    return 0;
}
