static int program_segment_alloc_map(struct Env *e, void *va, uint32 length)
{
	// TODO: LAB6 Hands-on: fill this function.
	// Comment the following line
	// panic("Function is not implemented yet!");
	uint32 start_va = ROUNDDOWN((uint32)va,PAGE_SIZE) ;
	uint32 end_va = ROUNDUP(((uint32)va)+length,PAGE_SIZE) ;

	// You should round round "va + length" up, and "va" down.
	// your code here ...

	for( ; start_va<end_va ; start_va+=PAGE_SIZE)
	{
		struct Frame_Info *ptr_frame = NULL ;
		int ret = allocate_frame(&ptr_frame) ;
		if (ret == E_NO_MEM) { return E_NO_MEM ; }
		ret = map_frame(e->env_pgdir ,ptr_frame,(void *)start_va,PERM_USER|PERM_WRITEABLE); // created page_directory for the env
		if(ret == E_NO_MEM) {return E_NO_MEM;}
	}
	return 0;
}

