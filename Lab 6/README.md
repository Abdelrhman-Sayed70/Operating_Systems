# Intel Memory Management IV “Loading and running user program”

## Program binary & program environment 
- Program Binary : exe -> machine code (0's & 1's) 
- program environment [STRUCT] : data structure that kernel uses to hold information about loaded program binary (exe). each instance of the program has its Env.
- Program Binary -> program environment (1 to N)

## Environment information

1. The virtual address of the loaded program 
2. Program Status (Ready, Run, Block…).
3. Program registers
4. The environment ID.
5. ptr_user directory 
6. each program has its directory table   

## FOS progrmas 
`in user folder`

contains all programs FOS can run like  

- fos_add.c
- fos_game.c 

## Program in FOS  
`kern/user_environment.c`

```c
// to declare the start pointer in your code
DECLARE_START_OF(prog_name)
```

```c
// to get the pointer to the start of “fos_input” binary file in memory
uint8 *ptr_start = PTR_START_OF(prog_name);
```


