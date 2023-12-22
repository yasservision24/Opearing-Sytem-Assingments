//THIRD FINAL
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define BRIDGE_CAPACITY 5

sem_t leftCars, rightCars, bridgeCapacity;

void passing(int dir, int id) {
    printf("Car %d from %s side is crossing the bridge.\n", id, (dir == 0) ? "left" : "right");
}

void* left(void* args) {
    int id = *((int*)args);

    sem_wait(&leftCars);
    sem_wait(&bridgeCapacity);

    // Signal to right cars that left car is on the bridge
    sem_post(&leftCars);

    passing(0, id);

    // Simulate crossing the bridge
    sleep(1);

    sem_post(&bridgeCapacity);

    pthread_exit(NULL);
}

void* right(void* args) {
    int id = *((int*)args);

    sem_wait(&rightCars);
    sem_wait(&bridgeCapacity);

    // Signal to left cars that right car is on the bridge
    sem_post(&rightCars);

    passing(1, id);

    // Simulate crossing the bridge
    sleep(1);

    sem_post(&bridgeCapacity);

    pthread_exit(NULL);
}

int main() {
    int numLeftCars, numRightCars;

    printf("Enter the number of cars on the left side: ");
    scanf("%d", &numLeftCars);
    printf("Enter the number of cars on the right side: ");
    scanf("%d", &numRightCars);

   

    sem_init(&leftCars, 0, 1);
    sem_init(&rightCars, 0, 1);
    sem_init(&bridgeCapacity, 0, BRIDGE_CAPACITY);

    pthread_t leftThreads[numLeftCars], rightThreads[numRightCars];
    int leftIDs[numLeftCars], rightIDs[numRightCars];

    for (int i = 0; i < numLeftCars; i++) {
        leftIDs[i] = i + 1;
        pthread_create(&leftThreads[i], NULL, left, (void*)&leftIDs[i]);
    }

    for (int i = 0; i < numRightCars; i++) {
        rightIDs[i] = i + 1;
        pthread_create(&rightThreads[i], NULL, right, (void*)&rightIDs[i]);
    }

    for (int i = 0; i < numLeftCars; i++) {
        pthread_join(leftThreads[i], NULL);
    }

    for (int i = 0; i < numRightCars; i++) {
        pthread_join(rightThreads[i], NULL);
    }

    sem_destroy(&leftCars);
    sem_destroy(&rightCars);
    sem_destroy(&bridgeCapacity);

    return 0;
}
