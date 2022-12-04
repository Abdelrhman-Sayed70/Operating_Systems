# Intel Memory Management IV “Loading and running user program”

## Program binary & program environment 
- Program Binary : exe -> machine code (0's & 1's) 
- program environment [STRUCT] : data structure that kernel uses to hold information about loaded program binary (exe). each instance of the program has its Env.

## Environment information

1. The virtual address of the loaded program 
2. Program Status (Ready, Run, Block…).
3. Program registers
4. The environment ID.
