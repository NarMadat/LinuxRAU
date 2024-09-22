#include <iostream>
#include "complex.h"
#include "sort.h"

int main() {
	Complex numbers[] = {Complex(3,4), Complex(1,2)};
	int size = sizeof(numbers) / sizeof(numbers[0]);

	sort(numbers, size);

	for (int i = 0; i < size; i++){
		std::cout << numbers[i] << std::endl;
	}

	return 0;
}


