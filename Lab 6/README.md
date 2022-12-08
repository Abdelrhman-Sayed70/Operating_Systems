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
6. each program (environment) has its directory table   

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
`contains all FOS programs info`
```c
struct UserProgramInfo userPrograms[] = {
	{ "fos_helloWorld", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_helloWorld), 0 },
	{ "fos_add", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_add), 0},
	{ "fos_alloc", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_alloc), 0},
	{ "fos_input", "Created by FOS team, fos@nowhere.com", PTR_START_OF(fos_input), 0},
	{ "fos_game", "Created by FOS team, fos@nowhere.com", PTR_START_OF(game), 0},
	// env is set to 0 as no env created yet for any program so i should create env
};
```

## Code is segments 
- source code is splitted into segments  
- To successfully load the binary and make it ready for execution we need to load each segment to its right place in memory
- The information about program segments is stored in "struct ProgramSegment" located in "user_environment.c". 

## ProgramSegment
`kern/user_environment.c`

```c
struct ProgramSegment {
	uint8 *ptr_start;  //start address of this segment in memory (the memory address where it is saved before loading)
	uint32 size_in_file;
	uint32 size_in_memory;
	uint8 *virtual_address; // mapped to which virtual_address

	// for use only with PROGRAM_SEGMENT_FOREACH
	uint32 segment_id;
};
```
## size in file VS size in memory 

- file : size of the written code 
- memory : size of any thing in the code e.g (int arr[1024] will assign 1024 free space in memory)

`size in memory >= size in file`

## iterate over all segements  
`kern/user_environment.c` 

```c
PROGRAM_SEGMENT_FOREACH(Seg, ptr_program_start)	
```

## env_create
`kern/user_environment.c`

`load exe in RAM`

- create empty env object [OS role]
- create directory table for the env. how? dir = 4 KB = 1 frame. so allocate 1 frame for the directory table of the environment
- for each segment [running program directory table should take the control ]
	- allocate frame for the current seg 
	- map  
	- copy seg binary form Disk to RAM 
- initialize instruction pointer to the start of the code 
- allocate memory for stack 

```txt
Note : when we create env for specific program we should swithc the control of the directory table to the created program directory table (not OS ptr_page_dir) and at the end of the process the control goes back to OS ptr_page_dir    
```
