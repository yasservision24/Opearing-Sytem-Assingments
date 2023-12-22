The main.c file contains the source code for the program.
The program defines a fact() function to calculate the factorial of a given number using recursion.
It also defines a fibn() function to calculate the Fibonacci series of a given number using recursion.
The main program creates a child process using the vfork() system call.
If vfrok returns a 0 it means child process is running and if positive value it means parent process is running.
In the child process, the factorial of 4 is calculated using the fact() function, and the result is displayed.
In the parent process, the Fibonacci series up to 16 is calculated using the fibn() function, and the result is displayed.
The parent process waits for the child process to complete before displaying its own output.Or parent wait for the child to die.

Compilation and Execution
To compile the program

Open a terminal window.

Navigate to the directory containing main.c and the provided Makefile.

Run the following command:
"make"

This compiles the program and generates an executable named program.

To run the program:
"./run"