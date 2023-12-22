Parent Process and Child Process
The program begins by using the fork() system call to create a new child process. The fork() function duplicates the current process, resulting in two identical processes running in separate memory spaces. The return value of fork() is different for the parent and child processes.

In the parent process, fork() returns the process ID (PID) of the child.
In the child process, fork() returns 0

In the parent process:

Statement A (printf("A) Parent (P) is having ID %d\n", getpid()); prints the process ID of the parent.
Statement C (printf("C) ID of P's Child is %d\n", child_pid); prints the child process ID.
The wait(NULL) call suspends the parent process until the child process completes its execution.
Statement B (printf("B) ID of P's Child is %d\n", child_pid); prints the child process ID again.
In the child process:

Statement C (printf("C) Child is having ID %d\n", getpid()); prints the child process ID.
Statement D (printf("D) My Parent ID is %d\n", getppid()); prints the parent process ID


Compilation and Execution
To compile the program

Open a terminal window.

Navigate to the directory containing main.c and the provided Makefile.

Run the following command:
"make"

This compiles the program and generates an executable named program.

To run the program:
"./run"