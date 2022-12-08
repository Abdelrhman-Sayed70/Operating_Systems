//
// Allocates a new env and loads the named user program into it.
struct UserProgramInfo* env_create(char* user_program_name)
{
	//[1] get pointer to the start of the "user_program_name" program in memory
	// Hint: use "get_user_program_info" function,
	// you should set the following "ptr_program_start" by the start address of the user program
	uint8* ptr_program_start = 0;

	struct UserProgramInfo* ptr_user_program_info = get_user_program_info(user_program_name);

	if (ptr_user_program_info == 0)
		return NULL ;

	ptr_program_start = ptr_user_program_info->ptr_start ;
	//===========================================================================================

	//[2] allocate new environment, (from the free environment list)
	//if there's no one, return NULL
	// Hint: use "allocate_environment" function
	struct Env* e = NULL;
	if(allocate_environment(&e) == E_NO_FREE_ENV)
	{
		return 0;
	}
	//===========================================================================================

	// TODO: LAB6 Hands-on: fill this part.
	// Comment the following line
    // panic("env_create: directory creation is not implemented yet!");

	//[3] allocate a frame for the page directory, Don't forget to set the references of the allocated frame.
	//if there's no free space, return NULL
	//your code here . . .
	struct Frame_Info *ptr_new_dir = NULL ;
	int retu = allocate_frame(&ptr_new_dir);
	if (retu == E_NO_MEM) {
		cprintf("faild to allocate Environment directory table\n") ;
		return NULL ;
	}
	ptr_new_dir->references = 1 ;
	//===========================================================================================

	//[4] copy kernel directory into the new directory
	//your code here . . .
	uint32 physical_address_of_new_dir = to_physical_address(ptr_new_dir);
	uint32 *ptr_new_dir1 = K_VIRTUAL_ADDRESS(physical_address_of_new_dir);
	// ptr_page_directory is 4KB = 1024B
	// i want to share FOS to the current env
	for (int i = 0; i < 1024; i++) {
		ptr_new_dir1[i] = ptr_page_directory[i];
	}

	//[5] set e->env_pgdir to page directory virtual address
	//and e->env_cr3 to page directory physical address.
	//your code here
	e->env_cr3 = physical_address_of_new_dir;
	e->env_pgdir = ptr_new_dir1;

	//===========================================================================================

	//Complete other environment initializations, (envID, status and most of registers)
	complete_environment_initialization(e);

	//[6] update the UserProgramInfo in userPrograms[] corresponding to this program
	ptr_user_program_info->environment = e;

	// We want to load the program into the user virtual space
	// each program is constructed from one or more segments,
	// each segment has the following information grouped in "struct ProgramSegment"
	//	1- uint8 *ptr_start: 	start address of this segment in memory
	//	2- uint32 size_in_file: size occupied by this segment inside the program file,
	//	3- uint32 size_in_memory: actual size required by this segment in memory
	// 	usually size_in_file < or = size_in_memory
	//	4- uint8 *virtual_address: start virtual address that this segment should be copied to it

	//switch to user page directory
	// rcr3() reads cr3, lcr3() loads cr3
	int32 kern_phys_pgdir = rcr3() ; // read cr3
	lcr3(e->env_cr3) ; // load cr3

	//load each program segment into user virtual space
	struct ProgramSegment* seg = NULL;  //use inside PROGRAM_SEGMENT_FOREACH as current segment information

	PROGRAM_SEGMENT_FOREACH(seg, ptr_program_start)
	{
		//============================================================
		//[7] allocate space for current program segment and map it at
		//seg->virtual_address
		// if program_segment_alloc_map() returns E_NO_MEM, call env_free() to     free all environment memory,
		// zero the UserProgramInfo* ptr->environment then return NULL

		//Hands On 2: implementation of function program_segment_alloc_map()
		int ret = program_segment_alloc_map(e, (void *)seg->virtual_address, seg->size_in_memory) ;

		if (ret == E_NO_MEM)
		{
			cprintf("Load program failed: no enough memory\n\nProgram will be unloaded now...\n\n");
			env_free(e);
			ptr_user_program_info->environment = NULL;
			return NULL;
		}
		//============================================================

		//[8] copy program segment from (seg->ptr_start) to
		//(seg->virtual_address) with size seg->size_in_file
		uint8 *src_ptr = (uint8 *)(seg->ptr_start) ; // start pointer of the source code
		uint8 *dst_ptr = (uint8 *) seg->virtual_address; // virtual address mapped to.

		int i ;
		for(i = 0 ; i < seg->size_in_file; i++)
		{
			*dst_ptr = *src_ptr ;
			dst_ptr++ ;
			src_ptr++ ;
		}

		// Initialize the rest of the program segment the rest
		// (seg->size_in_memory - seg->size_in_file) bytes
		// By Zero
		for(i = seg->size_in_file ; i < seg->size_in_memory ; i++)
		{
			*dst_ptr = 0 ;
			dst_ptr++;
		}
	}

	//[9] now set the entry point of the environment
	set_environment_entry_point(ptr_user_program_info);


	//[10] Allocate and map one page for the program's initial stack
	// at virtual address USTACKTOP - PAGE_SIZE.
	// if there is no free memory, call env_free() to free all env. memory,
	// zero the UserProgramInfo* ptr->environment then return NULL


	// allocate 1 frame for stack
	struct Frame_Info *pp = NULL;
	if (allocate_frame(&pp) == E_NO_MEM)
	{
		cprintf("Load program failed: no enough memory\n\nProgram will be unloaded now...\n\n");
		env_free(e);
		ptr_user_program_info->environment = NULL;
		return NULL;
	}

	// map the allocated page
	void* ptr_user_stack_bottom = (void *)(USTACKTOP - PAGE_SIZE);
	int ret = map_frame(e->env_pgdir, pp, ptr_user_stack_bottom, PERM_USER|PERM_WRITEABLE);

	if (ret == E_NO_MEM)
	{
		cprintf("Load program failed: no enough memory\n\nProgram will be unloaded now...\n\n");
		env_free(e);
		ptr_user_program_info->environment = NULL;
		return NULL;
	}

	//initialize new page by 0's
	memset(ptr_user_stack_bottom, 0, PAGE_SIZE);

	//[11] switch back to the page directory exists before segment loading
	lcr3(kern_phys_pgdir) ;

	return ptr_user_program_info;
}