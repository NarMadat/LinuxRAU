#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/wait.h>
#include <stdexcept>

int calculate_prime(int n) {
    if (n < 1) return -1;

    std::vector<int> primes;
    int num = 2;

    while (primes.size() < static_cast<std::size_t>(n)) {
        bool is_prime = true;
        for (int p : primes) {
            if (p * p > num) break;
            if (num % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) primes.push_back(num);
        ++num;
    }
    return primes.back();
}

void calc() {
    int pipe1[2], pipe2[2]; 


    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    int child_id = fork(); 

    if (child_id < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_id == 0) {  
        close(pipe1[1]); 
        close(pipe2[0]); 

        const int BUFFER_SIZE = 20;
        char c[BUFFER_SIZE];


        int is_read = read(pipe1[0], c, BUFFER_SIZE - 1);
        if (is_read == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        c[is_read] = '\0';
	std::string str2(c);

	if(str2 == "exit"){
		close(pipe1[0]);
		close(pipe2[1]);
		exit(0);
	}

        int number;
        try {
            number = std::stoi(c); 
        } catch (const std::exception& e) {
            std::cerr << "Invalid input: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        int result = calculate_prime(number); 
        std::string str = std::to_string(result);


        if (write(pipe2[1], str.c_str(), str.size()) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0); 
    } else {  
        close(pipe2[1]);
        close(pipe1[0]); 

        std::string inp;
        std::cout << "Enter a number (or 'exit' to quit): ";
        if (!(std::cin >> inp)) {
            std::cerr << "Error reading input" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (inp == "exit") {
	    write(pipe1[1], "exit", 4);
    		close(pipe1[1]);
            close(pipe2[0]);
            exit(0);
        }


        if (write(pipe1[1], inp.c_str(), inp.size()) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }

        wait(nullptr); 

        const int BUFFER_SIZE = 20;
        char c[BUFFER_SIZE];


        int is_read = read(pipe2[0], c, BUFFER_SIZE - 1);
        if (is_read == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        c[is_read] = '\0';

        std::cout << "Result: " << c << std::endl;

        close(pipe1[1]);
        close(pipe2[0]);
    }
}

int main() {
    while (true) {
        calc();
    }
    return 0;
}

