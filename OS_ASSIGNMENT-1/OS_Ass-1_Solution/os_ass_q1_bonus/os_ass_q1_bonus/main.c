#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int func_fact(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * func_fact(n - 1);
}

void func_fibn(int n) {
    int a = 0, b = 1, nt;

    printf("Parent:fibonacci Series: ");

    for (int i = 1; i <= n; i++) {
        printf("%d ", a);
        nt = a + b;
        a = b;
        b = nt;
    }

    printf("\n");
}

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork(); 
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    } else if (child_pid == 0) {
        int fact = func_fact(4);
        printf("Child: factorial of of 4 is %d\n", fact);
    } else {

        func_fibn(16);
        wait(&status);  
   
    }

    return 0;
}
