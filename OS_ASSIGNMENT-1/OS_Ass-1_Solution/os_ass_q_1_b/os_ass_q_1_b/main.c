#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int fibn(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibn(n - 1) + fibn(n - 2);
}
int fact(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * fact(n - 1);
}
int main() {
    pid_t pid = vfork(); 

    if (pid < 0) {
        perror("vfork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        int result = fact(4);
        printf("Child process: fact of 4 is %d\n", result);
        _exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int fib[16];
        printf("Parent process: fibn series up to 16 elements:- ");
        for (int i = 0; i < 16; i++) {
            fib[i] = fibn(i);
            printf("%d ", fib[i]);
        }
        printf("\n");

        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        
    }

    return 0;
}
