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
//to declare the start pointer in your code
DECLARE_START_OF(prog_name)		
//to get the pointer to the start of “fos_input” binary file in memory
uint8 *ptr_start = PTR_START_OF(prog_name) 
```

## Env struct
`inc/environment_definitions.h` 
`contains all info needed about environment`
```c
struct Env {
	struct Trapframe env_tf;	// Saved registers
	LIST_ENTRY(Env)
	prev_next_info;	// Free list link pointers
	int32 env_id;			// Unique environment identifier
	int32 env_parent_id;		// env_id of this env's parent
	unsigned env_status;		// Status of the environment
	uint32 env_runs;		// Number of times environment has run

	// Address space
	uint32 *env_pgdir; // Kernel virtual address of page dir
	uint32 env_cr3;	   // Physical address of page dir

};
```

## UserProgramInfo Struct
`kern/user_environment.h`
`contains infor needed about user program`
```c
struct UserProgramInfo {
	const char *name;
	const char *desc;
	uint8* ptr_start;
	struct Env* environment;
};
```

## UserPrograms[] array 
`kern/user_environment.c` 

```c
struct UserProgramInfo userPrograms[] = {
	{ "fos_helloWorld", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_helloWorld), 0 },
	{ "fos_add", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_add), 0},
	{ "fos_alloc", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_alloc), 0},
	{ "fos_input", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_input), 0},
	{ "fos_game", "Created by FOS team, fos@nowhere.com", PTR_START_OF(game), 0},
};
```

