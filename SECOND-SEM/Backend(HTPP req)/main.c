#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define HOST "httpforever.com"
#define PORT 80
#define REQUEST "GET / HTTP/1.1\r\nHost: httpforever.com\r\nConnection: close\r\n\r\n"
#define BUFFER_SIZE 4096

int main() {
    int sock;
    struct sockaddr_in server;
    struct hostent *host_info;
    char buffer[BUFFER_SIZE];
    
    host_info = gethostbyname(HOST);
    if (!host_info) {
        perror("Ошибка получения IP-адреса");
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Ошибка создания сокета"); // get r1 http://r2.com
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memcpy(&server.sin_addr, host_info->h_addr, host_info->h_length);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Ошибка подключения");
        close(sock);
        return 1;
    }

    if (send(sock, REQUEST, strlen(REQUEST), 0) < 0) {
        perror("Ошибка отправки запроса");
        close(sock);
        return 1;
    }

    FILE *file = fopen("httpforever.html", "w");
    if (!file) {
        perror("Ошибка открытия файла");
        close(sock);
        return 1;
    }

    while (1) {
        ssize_t received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (received <= 0) break;
        buffer[received] = '\0';
        fprintf(file, "%s", buffer);
    }

    fclose(file);
    close(sock);
    return 0;
}
