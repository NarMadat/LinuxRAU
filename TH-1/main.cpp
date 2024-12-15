#include <iostream>
#include <vector>
#include <pthread.h>
#include <numeric>
#include <cstdlib>
#include <chrono>



void* compute_partial_sum(void* arg) {
    auto* data = static_cast<std::pair<const std::vector<int>*, std::pair<size_t, size_t>>*>(arg);
    const auto& array = *data->first;
    size_t start = data->second.first, end = data->second.second;
    auto* result = new long long(std::accumulate(array.begin() + start, array.begin() + end, 0LL));
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) return 1;

    size_t N = std::stoull(argv[1]);
    size_t M = std::stoull(argv[2]);

    std::vector<int> array(N);
    for (size_t i = 0; i < N; ++i) array[i] = std::rand() % 100;

    auto start_time = std::chrono::high_resolution_clock::now(); // sksvec 1
    long long sum_without_threads = std::accumulate(array.begin(), array.end(), 0LL);
    auto end_time = std::chrono::high_resolution_clock::now(); // prcav 1
    std::chrono::duration<double> duration_without_threads = end_time - start_time; // DWT 

    start_time = std::chrono::high_resolution_clock::now();
    std::vector<pthread_t> threads(M);
    std::vector<std::pair<const std::vector<int>*, std::pair<size_t, size_t>>> thread_args(M);

    size_t chunk_size = N / M;
    for (size_t i = 0; i < M; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == M - 1) ? N : start + chunk_size;
        thread_args[i] = { &array, {start, end} };
        pthread_create(&threads[i], nullptr, compute_partial_sum, &thread_args[i]);
    }

    long long sum_with_threads = 0;
    for (size_t i = 0; i < M; ++i) {
        void* result;
        pthread_join(threads[i], &result);
        sum_with_threads += *static_cast<long long*>(result);
        delete static_cast<long long*>(result);
    }

    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_with_threads = end_time - start_time;

    std::cout << "time arandz thread " << duration_without_threads.count() << " seconds\n";
    std::cout << "time thredov" << M << " threads " << duration_with_threads.count() << " varkyan\n";

    return 0;
}
