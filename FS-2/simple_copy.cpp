#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int buffer_size = 4096;

	if(argc != 3) {
		std::cout << "Error. Please my dear student or dasaxos, enter true word";
		return 1;
	}

	const char* sourceFile = argv[1];
	const char* destFile = argv[2];


	int src_fd = open(sourceFile, O_RDONLY);
	if(src_fd < 0) {
		std::cout << "Error. I cant open this file my dear student or dasaxos";
		return 1;
	}

	int second_fd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(second_fd < 0) {
		std::cout << "Error. I cant open or create this file my dear ALLL";
		return 1;
	}

	char buffer[buffer_size];
    	int bytesRead;
    	while ((bytesRead = read(src_fd, buffer, buffer_size)) > 0) {
        	int bytesWritten = write(second_fd, buffer, bytesRead);
        	if (bytesWritten != bytesRead) {
            		std::cout << "Error. I dont know why!";
           		close(src_fd);
            		close(second_fd);
            		return 1;
        	}
    	}	

	close(src_fd);
	close(second_fd);

	return 0;
}
