//FINAL FIRST 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t bowls[2];
pthread_cond_t can_eat[NUM_PHILOSOPHERS];

void eating(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    usleep(200000);  // Simulate eating time
}

void thinking(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    usleep(200000);  // Simulate thinking time
}

void* philosopher(void* args) {
    int philosopher_id = *((int*)args);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        thinking(philosopher_id);

        // Pick up forks and bowl
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
        pthread_mutex_lock(&bowls[0]);
        
        // Start eating
        eating(philosopher_id);

        // Release forks and bowl
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
        pthread_mutex_unlock(&bowls[0]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks and conditional variables
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&can_eat[i], NULL);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_mutex_init(&bowls[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&can_eat[i]);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_mutex_destroy(&bowls[i]);
    }

    return 0;
}



