int command_writeblock(int number_of_arguments, char **arguments)
{
	// (write_block)(physical address)
	// virtual address  = physical address + KERNEL_BASE
	// physical_address = virtual_address - KERNEL_BASE
	int physical_address = strtol(arguments[1],NULL,16) ;
	int virtual_address = physical_address + KERNEL_BASE ;
	char *ptr = (char *)virtual_address ;
	while(1){
		char ch[5] ;
		readline("Write : ",ch) ;
		if (ch[0] == '$') {break ;}
		*ptr = ch[0] ;
		ptr++ ;
	}
	return 0 ;
}