#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("uncorrect adress");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        printf("enter message dear: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        
        send(sock, buffer, strlen(buffer), 0);

        
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);

        if (bytes_received <= 0) {
            printf("server disconnected.\n");
            break;
        }

        printf("server response is : %s\n", buffer);
    }

    close(sock);
    return 0;
}