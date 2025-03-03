#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PHILOSOPHERS 5

sem_t stick[PHILOSOPHERS];

void philosopher(int id) {
    srand(getpid());

    while (1) {
        printf("философ думает \n", id);
        usleep(rand() % 500000);

        if (id == 0) {
            sem_wait(&stick[(id + 1) % PHILOSOPHERS]);
            sem_wait(&stick[id]);
        } else {
            sem_wait(&stick[id]);
            sem_wait(&stick[(id + 1) % PHILOSOPHERS]);
        }

        printf("филсоф кушает ам-ням-ням\n", id);
        usleep(rand() % 500000);

        sem_post(&stick[id]);
        sem_post(&stick[(id + 1) % PHILOSOPHERS]);
    }
}

int main() {
    pid_t pids[PHILOSOPHERS];

    for (int i = 0; i < PHILOSOPHERS; i++) {
        sem_init(&stick[i], 1, 1);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            philosopher(i);
            exit(0);
        }
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        wait(NULL);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        sem_destroy(&stick[i]);
    }

    return 0;
}
