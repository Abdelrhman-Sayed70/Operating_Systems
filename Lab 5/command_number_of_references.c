//[1] Number of references on the given physical address
int command_nr(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "nr"
	//Comment the following line
	//panic("Function is not implemented yet!");

	// (nr)(physical_address)
	uint32 physical_address = strtol(arguments[1],NULL,16) ;
	struct Frame_Info *ptr_Frame_Info ;
	ptr_Frame_Info = to_frame_info(physical_address) ;
	cprintf("number of references of the frame of this physical_address is : %d\n" ,ptr_Frame_Info->references) ;
	return 0;
}