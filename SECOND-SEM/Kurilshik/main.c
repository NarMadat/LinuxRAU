#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define SMOKERS 3

sem_t sem_barber;
sem_t sem_smoker[SMOKERS];

volatile sig_atomic_t running = 1;

void signal_handler(int signum) {
    running = 0;
}

void smoker(int id, char missing_item) {
    while (running) {
        sem_wait(&sem_smoker[id]);
        if (!running) break;
        printf("%c\n", missing_item);
        fflush(stdout);
        usleep(500000);
        sem_post(&sem_barber);
    }
    exit(0);
}

void bartender() {
    char input;
    while (scanf(" %c", &input) == 1) {
        if (input == 't') sem_post(&sem_smoker[0]);
        else if (input == 'p') sem_post(&sem_smoker[1]);
        else if (input == 'm') sem_post(&sem_smoker[2]);
        sem_wait(&sem_barber);
    }

    for (int i = 0; i < SMOKERS; i++) kill(0, SIGTERM);
    exit(0);
}

int main() {
    signal(SIGTERM, signal_handler);

    sem_init(&sem_barber, 1, 1);
    for (int i = 0; i < SMOKERS; i++) sem_init(&sem_smoker[i], 1, 0);

    pid_t pids[SMOKERS];
    char missing_items[SMOKERS] = {'T', 'P', 'M'};

    for (int i = 0; i < SMOKERS; i++) {
        pids[i] = fork();
        if (pids[i] == 0) smoker(i, missing_items[i]);
    }

    bartender();
    return 0;
}
