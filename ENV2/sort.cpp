#include "sort.h"

void sort(Complex arr[], int size) {
	for(int i = 0; i < size - 1; i++) {
		for(int j = 0; j < size - i -1; i++) {
			if(arr[j].abs() > arr[j + 1].abs()) {
				Complex temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}


