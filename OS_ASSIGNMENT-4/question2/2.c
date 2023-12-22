#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int counter = 0;
int totalSeats;
int counter1;
int rideSignaled = 0;
sem_t semaphore;
sem_t offboardSemaphore;
pthread_cond_t loadCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t loadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rideCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t rideMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t unloadCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t unloadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t counterMutex = PTHREAD_MUTEX_INITIALIZER;
sem_t boardSemaphore;

void load() {
    printf("Loading...\n");
    sleep(1);
    printf("Loading complete!\n");
    pthread_cond_broadcast(&loadCond);
}

void board() {
    sem_wait(&semaphore);
    pthread_mutex_lock(&counterMutex);

    if (counter < totalSeats) {
        counter++;
        printf("Passenger boarded. Total passengers boarded: %d\n", counter);

        if (counter == totalSeats) {
            pthread_mutex_lock(&rideMutex);
            rideSignaled = 1;
            pthread_cond_signal(&rideCond);
            pthread_mutex_unlock(&rideMutex);
        }
    }

    pthread_mutex_unlock(&counterMutex);
    sem_post(&semaphore);
}

void ride() {
    pthread_mutex_lock(&rideMutex);

    while (!rideSignaled) {
        pthread_cond_wait(&rideCond, &rideMutex);
    }

    printf("Riding...\n");
    sleep(2);
    printf("Ride complete!\n");

    pthread_mutex_unlock(&rideMutex);
}

void unload() {
    printf("Unloading...\n");
    sleep(1);
    printf("Unloading complete!\n");
}

void offboard() {
    sem_wait(&offboardSemaphore);
    pthread_mutex_lock(&counterMutex);

    while (counter1 > 0) {
        counter1--;
        printf("Passenger offboarded. Total passengers remaining: %d\n", counter1);
    }

    pthread_mutex_unlock(&counterMutex);
    sem_post(&offboardSemaphore);
}

void *carThread(void *arg) {
    int numCarSeats = *((int *)arg);

    printf("Car thread started with %d car seats.\n", numCarSeats);

    load();
    ride();
    unload();
    pthread_cond_broadcast(&unloadCond);

    pthread_exit(NULL);
}

void *passengerThread(void *arg) {
    int passengerNumber = *((int *)arg);

    pthread_mutex_lock(&loadMutex);
    pthread_cond_wait(&loadCond, &loadMutex);
    pthread_mutex_unlock(&loadMutex);

    sem_wait(&boardSemaphore);

    if (counter < totalSeats) {
        board();
        sem_post(&boardSemaphore);

        pthread_mutex_lock(&unloadMutex);
        pthread_cond_wait(&unloadCond, &unloadMutex);
        pthread_mutex_unlock(&unloadMutex);

        offboard();

        pthread_exit(NULL);
    } else {
        sem_post(&boardSemaphore);
        pthread_exit(NULL);
    }
}

int main() {
    pthread_t carThreadID;
    pthread_t *passengerThreads;
    int numPassengers, numCarSeats, numRounds;
    printf("Enter the number of passengers: ");
        scanf("%d", &numPassengers);

        printf("Enter the number of car seats: ");
        scanf("%d", &numCarSeats);

        if (numPassengers <= numCarSeats) {
            printf("Not enough passengers for the available car seats!\n");
            return 1;
        }

        totalSeats = numCarSeats;
        counter1 = numCarSeats;


    while (1) {
        counter=0;
        counter1=numCarSeats;
        if (sem_init(&semaphore, 0, 1) != 0 || sem_init(&offboardSemaphore, 0, 1) != 0 ||
            sem_init(&boardSemaphore, 0, 1) != 0) {
            fprintf(stderr, "Semaphore initialization error\n");
            return 1;
        }



        if (pthread_create(&carThreadID, NULL, carThread, (void *)&numCarSeats)) {
            fprintf(stderr, "Error creating car thread\n");
            return 1;
        }

        passengerThreads = (pthread_t *)malloc(numPassengers * sizeof(pthread_t));
        if (passengerThreads == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }

        for (int i = 0; i < numPassengers; ++i) {
            if (pthread_create(&passengerThreads[i], NULL, passengerThread, (void *)&i)) {
                fprintf(stderr, "Error creating passenger thread\n");
                return 1;
            }
        }

        if (pthread_join(carThreadID, NULL)) {
            fprintf(stderr, "Error joining car thread\n");
            return 1;
        }

        for (int i = 0; i < numPassengers; ++i) {
            if (pthread_join(passengerThreads[i], NULL)) {
                fprintf(stderr, "Error joining passenger thread\n");
                return 1;
            }
        }


        printf("Car and passenger threads have finished.\n");

        sem_destroy(&semaphore);
        sem_destroy(&offboardSemaphore);
        sem_destroy(&boardSemaphore);


        free(passengerThreads);
    }


    return 0;
}
