int command_set_permission_old(int number_of_arguments, char **arguments)
{
	// (sp_old)(virtual_address)(char(r or w))
	// idea : if char is r then reset the Read/ Write bit else set this bit

	int virtual_address = strtol(arguments[1],NULL,16);
	char permission = arguments[2][0] ;

	uint32 *ptr_page_table = NULL ;
	int ret = get_page_table(ptr_page_directory,virtual_address,&ptr_page_table) ;
	if (ptr_page_table!=NULL)
	{
		if (permission  == 'r') {
			// reset Read/ Write bit
			ptr_page_table[PTX(virtual_address)] &= ~(PERM_WRITEABLE) ;
		}
		else if (permission == 'w') {
			// set Read/ Write bit
			ptr_page_table[PTX(virtual_address)] |= (PERM_WRITEABLE) ;
		}
	}
	tlb_invalidate((void *)NULL, (void *)virtual_address); // refresh cache
	return 0 ;
}