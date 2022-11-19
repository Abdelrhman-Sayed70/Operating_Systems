//[3] Free Page: Un-map a single page at the given virtual address in the user space
int command_fp(int number_of_arguments, char **arguments)
{
	//TODO: LAB5 Example: fill this function. corresponding command name is "fp"
	//Comment the following line
	//panic("Function is not implemented yet!");

	uint32 virtual_address = strtol(arguments[1], NULL, 16);
	// Un-map the page at this address
	unmap_frame(ptr_page_directory, (void*)virtual_address);

	return 0;
}