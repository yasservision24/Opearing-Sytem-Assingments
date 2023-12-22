Code Logic:

The fun_fact() function calculates the factorial of a given number recursively.
The fun_fibn() function generates the Fibonacci series up to 16.
The main part of the program uses the fork() system call to create a child process.
In the child process, the factorial is calculated and printed.
In the parent process, the Fibonacci series is generated and printed.
The child process waits for the parents process to complete using the wait() system call.

Makefile:

The Makefile provides rules for compiling the main.c
CC specifies the compiler to be used (gcc).
CFLAGS specifies the compiler flags (Wall for enabling warnings).
The all target compiles the program.
The program target compiles the source code.
The clean target removes the compiled executable.
Executable is formed by name run

To run the code type ./run