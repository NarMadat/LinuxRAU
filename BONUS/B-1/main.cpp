#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <pthread.h>

pthread_mutex_t mutex;

void print_file_content(const std::string &file_path)
{
    std::ifstream file(file_path);
    if (!file)
    {
        pthread_mutex_lock(&mutex);
        std::cerr << "i cant open it: " << file_path << std::endl;
        pthread_mutex_unlock(&mutex);
        return;
    }

    std::string line;
    pthread_mutex_lock(&mutex);
    std::cout << "yourr file consist this: " << file_path << " ---\n";
    pthread_mutex_unlock(&mutex);

    while (std::getline(file, line))
    {
        pthread_mutex_lock(&mutex);
        std::cout << line << std::endl;
        pthread_mutex_unlock(&mutex);
    }
    file.close();
}

void *process_directory(void *arg)
{
    std::string directory = *(std::string *)arg;
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            print_file_content(entry.path().string());
        }
    }
    return nullptr;
}

int main()
{
    pthread_mutex_init(&mutex, nullptr);

    std::string directory;
    std::cout << "enter please ";
    std::cin >> directory;

    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
    {
        std::cerr << "directory invalid !" << std::endl;
        return 1;
    }

    pthread_t thread;
    pthread_create(&thread, nullptr, process_directory, &directory);
    pthread_join(thread, nullptr);

    pthread_mutex_destroy(&mutex);
    return 0;
}
