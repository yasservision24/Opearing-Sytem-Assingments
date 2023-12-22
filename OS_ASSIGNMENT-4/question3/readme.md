Program Logic:
1. Semaphore Initialization:
leftCars and rightCars semaphores are initialized to 1, ensuring exclusive access to the bridge from each side.
bridgeCapacity semaphore is initialized to the maximum bridge capacity (BRIDGE_CAPACITY), limiting the total number of cars on the bridge.

2. Thread Functions (left and right):
left and right functions control access to the bridge using semaphores.
A car from the left side waits on the leftCars semaphore and the bridgeCapacity semaphore.
A car from the right side waits on the rightCars semaphore and the bridgeCapacity semaphore.
After crossing the bridge, the car releases the bridgeCapacity semaphore, allowing other cars to cross.

3. Signaling to Other Side:
To avoid potential deadlock, each car signals to the other side before releasing its own semaphore.
For example, a car from the left side signals to the right cars before releasing the leftCars semaphore.

4. Simulating Crossing the Bridge:
The sleep(1) statement simulates the time it takes for a car to cross the bridge.

Bridge Crossing Simulation
This program simulates the crossing of a bridge between two sides of a river by cars. The constraints are as follows:

Only one car from each side can access the bridge simultaneously.
The total number of cars on the bridge is limited to a certain capacity.
Cars must signal to the other side before releasing their own semaphore to avoid potential deadlocks.
Program Logic:

1. Semaphore Initialization:
leftCars and rightCars semaphores are initialized to 1, ensuring exclusive access to the bridge from each side.
bridgeCapacity semaphore is initialized to the maximum bridge capacity (BRIDGE_CAPACITY), limiting the total number of cars on the bridge.

sem_init(&leftCars, 0, 1);
sem_init(&rightCars, 0, 1);
sem_init(&bridgeCapacity, 0, BRIDGE_CAPACITY);

2. Thread Functions (left and right):
left and right functions control access to the bridge using semaphores.
A car from the left side waits on the leftCars semaphore and the bridgeCapacity semaphore.
A car from the right side waits on the rightCars semaphore and the bridgeCapacity semaphore.
After crossing the bridge, the car releases the bridgeCapacity semaphore, allowing other cars to cross.
sem_wait(&leftCars);
sem_wait(&bridgeCapacity);
// ... Crossing the bridge ...
sem_post(&bridgeCapacity);

3. Signaling to Other Side:
To avoid potential deadlock, each car signals to the other side before releasing its own semaphore.
For example, a car from the left side signals to the right cars before releasing the leftCars semaphore.

sem_post(&rightCars);  // Signal to right cars that left car is on the bridge
Similarly, a car from the right side signals to the left cars before releasing the rightCars semaphore.
sem_post(&leftCars);  // Signal to left cars that right car is on the bridge

4. Simulating Crossing the Bridge:
The sleep(1) statement simulates the time it takes for a car to cross the bridge.


Avoiding Concurrency Bugs:

Semaphore Usage:

Semaphores (leftCars, rightCars, and bridgeCapacity) are used to control access to shared resources and limit the number of cars on the bridge, preventing data corruption and ensuring proper synchronization.
Signaling to Other Side:

Signaling to the other side before releasing the semaphore helps avoid potential deadlocks. This ensures that even if one side is waiting, the other side gets the signal to proceed.
Semaphore Initialization:

Semaphores are initialized with appropriate initial values to represent the number of available resources and control access to shared sections.
Semaphore Destruction:

Semaphores are properly destroyed at the end of the program to release system resources.
Thread Joining:

The pthread_join function is used to wait for the completion of threads, ensuring that the main thread doesn't proceed before all cars have finished crossing the bridge.
This design ensures safe and concurrent execution while adhering to the specified constraints, avoiding common concurrency bugs such as data races and deadlocks.*/