This program demonstrates how to use different Linux scheduling policies for three processes.
Each process counts from 1 to 2^32, and we benchmark three scheduling policies: SCHED_OTHER, SCHED_RR, and SCHED_FIFO.
There are three child processes created using the fork() system call and each child process uses the execl() family of system calls to execute another C program responsible for counting.
The child processes, after creation, execute separate C programs that perform counting from 1 to 2^32.
These counting programs will measure the execution time using clock_gettime().
The parent process records the start time using clock_gettime() before forking the child processes.
The parent process waits for each child process to terminate using waitpid() to record the end time.
After all child processes finish, the parent process calculates the execution time for each child.
For histogram generation we used Python using the matplotlib, we used different colours to represent each scheduling process
This program provides insight into how different Linux scheduling policies affect the execution time of processes.