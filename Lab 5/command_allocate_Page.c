//[2] Allocate Page: If the given user virtual address is mapped, do nothing. Else, allocate a single frame and map it to a given virtual address in the user space
int command_ap(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "ap"
	//Comment the following line
	//panic("Function is not implemented yet!");

	// (ap)(virtual_address)

	// check
	uint32 virtual_address = strtol(arguments[1], NULL, 16) ;
	uint32 *ptr_page_table = NULL ;
	struct Frame_Info *ptr_Frame_Info = get_frame_info(ptr_page_directory, (void*)virtual_address, &ptr_page_table) ;
	if (ptr_Frame_Info != NULL){ return 0 ;}

	// allocate frame
	int ret  = allocate_frame(&ptr_Frame_Info) ;
	if (ret == E_NO_MEM){ return -1 ;}

	// map to RAM
	ret = map_frame(ptr_page_directory, ptr_Frame_Info, (void*)virtual_address, PERM_USER|PERM_WRITEABLE) ;
	if (ret == E_NO_MEM) {
		cprintf("No Free MEM\n") ;
		// Free the allocated frame
		free_frame(ptr_Frame_Info);
		return -1 ;
	}

	return 0 ;
}
