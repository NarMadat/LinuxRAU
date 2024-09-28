#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
int main(int argc, char* argv[]) {
    int buffer_size = 4096;
    if (argc != 2) {
        std::cout << "Error";
        return 1;
    }

    const char* filePath = argv[1];

    
    int fd = open(filePath, O_WRONLY);
    if (fd < 0) {
        std::cout << "Eror";
        return 1;
    }

    
    int fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize < 0) {
        std::cout << "Error";
        close(fd);
        return 1;
    }

    
    char buffer[buffer_size];
    memset(buffer, 0, buffer_size);

    lseek(fd, 0, SEEK_SET); 

    int bytesRemaining = fileSize;
    while (bytesRemaining > 0) {
        int bytesToWrite = (bytesRemaining < buffer_size) ? bytesRemaining : buffer_size;
        int bytesWritten = write(fd, buffer, bytesToWrite);
        if (bytesWritten < 0) {
            std::cout << "Error";
            close(fd);
            return 1;
        }
        bytesRemaining -= bytesWritten;
    }

    close(fd);
    return 0;
}

