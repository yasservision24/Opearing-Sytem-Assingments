#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t id;
    id = fork();

    if (id < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (id == 0) {
        
        printf("C) Child is having ID %d\n", getpid());
        printf("D) My Parent ID is %d\n", getppid());
    } else {
        
        printf("A) Parent (P) is having ID %d\n", getpid());
        wait(NULL);  
        printf("B) ID of P's Child is %d\n", id);
    }

    return 0;
}
