int command_readmem(int number_of_arguments, char **arguments)
{
	// (rum)(virtual address)
	// virtual address  = physical address + KERNEL_BASE
	int virtual_address = strtol(arguments[1],NULL,16) ;
	int physical_address = virtual_address - KERNEL_BASE ;
	char *ptr = (char *)virtual_address;
	cprintf("value at physical address: %x (virtual address: %x) is %c\n",physical_address,virtual_address,*ptr) ;
	return 0;
}