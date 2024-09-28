#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Error";
		return 1;
	}

	int fileDescriptor = open(argv[1], O_RDONLY);
	if (fileDescriptor < 0) {
		std::cout << "Error. I cant find the file";
		return 1;
	}

	int bufferSize = 1024;
	char buffer[bufferSize];
	int bytesRead;

	while((bytesRead = read(fileDescriptor, buffer, bufferSize)) > 0) {
		std::cout.write(buffer, bytesRead);
	}

	if (bytesRead < 0) {
		std::cout << "Error. I cant read this file my darling";
		close(fileDescriptor);
		return 1;

	}

	close(fileDescriptor);
	return 0;
}
