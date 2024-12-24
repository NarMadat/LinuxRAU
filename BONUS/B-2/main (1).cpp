#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>
#include <mutex>

struct ThreadData {
	int num1;
	int num2;
	std::string operation;
	int thread_id;
};


void* operation(void* arg) {
	ThreadData* data = new ThreadData(arg*);
	pthread_mutex_init mut;
	int result = 0;

	pthread_mutex_lock(&mut);
	if(data->operation == "s"){
		result = data->num1 + data->num2;
	} else if(data->operation == "m") {
		result = data->num1 * dara->num2;
	} else if(data->operation == "ss") {
		
		result = (data->num1 * data->num1) + (data->num2 * data->num2);
	} else {
		pthread_exit(nullptr)
	}
	pthread_mutex_unlock(&mut);
	std::cout << "thraed is " << data->thread_id << ": " << data->num1 << " " << data->operation << " " << data->num2 << "=" << result;
	pthread_exit(nullptr);da
        }


};


int main() {
	int n;
	std::cin >> n;

	std::vector<pthread_t> threads(n);
	std::vector<ThreeData> thread_data(n);

	for(int i = 1; i <n; i++) {
		int num1, num2;
		std::string operation;
		std::cin >> num1 >> num2 >> operation;

		thread_data[i] = {num1, num2, operation, i + 1};

		int x = pthread_create(&threads[i], nullptr, operation, &thread_data[i]);
		if(x != 0){
			std::cout << "Error";
			return 1;
		}
	}

	for(int i = 0; i < n; i++) {
		pthread_join(threads[i], nullptr);
	}

	return 0;	
	
};
