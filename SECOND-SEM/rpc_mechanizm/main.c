#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

double calculate(const char* op, double a, double b, int *error) {
    *error = 0;
    if (strcmp(op, "ADD") == 0) return a + b;
    if (strcmp(op, "SUB") == 0) return a - b;
    if (strcmp(op, "MUL") == 0) return a * b;
    if (strcmp(op, "DIV") == 0) {
        if (b == 0) {
            *error = 1;
            return 0;
        }
        return a / b;
    }
    *error = 1;
    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address); // еррорр -> 0
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) exit(EXIT_FAILURE);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, addr_len) == -1) {
        close(server_fd);
        exit(EXIT_FAILURE); // еррор -> 1
    }

    if (listen(server_fd, 5) == -1) {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&address, &addr_len);
        if (client_fd == -1) continue;

        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);

        if (bytes_read > 0) {
            char op[10];
            double a, b;
            int error;

            if (sscanf(buffer, "%3s %lf %lf", op, &a, &b) == 3) {
                double result = calculate(op, a, b, &error);
                char response[BUFFER_SIZE];

                if (!error) {
                    snprintf(response, BUFFER_SIZE, "%.2lf\n", result);
                } else {
                    snprintf(response, BUFFER_SIZE, "Error\n");
                }

                write(client_fd, response, strlen(response));
            } else {
                char msg[] = "Invalid command\n";
                write(client_fd, msg, strlen(msg));
            }
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
