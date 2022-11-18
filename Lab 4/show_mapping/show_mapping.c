int command_show_mapping(int number_of_arguments, char **arguments)
{
	//TODO: LAB4 Hands-on: fill this function. corresponding command name is "sm"
	//Comment the following line
	//panic("Function is not implemented yet!");

	//(sm)(VA)
	int virtual_address = strtol(arguments[1],NULL,16);
	//=====================================================================
	// 1-directory table index [DONE]
	uint32 directory_table_index = PDX(virtual_address) ;
	cprintf("Directory table index : %d\n",directory_table_index) ;
	//=====================================================================
	// 2-directory table entry  [DONE]
	uint32 directory_entry = ptr_page_directory[directory_table_index] ;
	cprintf("Directory table entry : %d\n",directory_entry) ;
	//=====================================================================
	// 3-page table virtual address (ptr page table) [need CONFIRMATION]
	uint32 *ptr_page_table = NULL ;
	get_page_table(ptr_page_directory,virtual_address,&ptr_page_table) ;
	if (ptr_page_table == NULL) { ptr_page_table = create_page_table(ptr_page_directory ,virtual_address) ; }
	cprintf("Virtual address of page table = %x\n" ,ptr_page_table);
	//=====================================================================
	// 4-page table index
	uint32 page_table_index = PTX(virtual_address) ;
	cprintf("Page table index : %d\n",page_table_index);
	//=====================================================================
	// 5-page table entry
	uint32 page_table_entry = ptr_page_table[page_table_index] ;
	cprintf("Page table entry : %d\n" ,page_table_entry) ;
 	//=====================================================================
	// 6-page table physical address [need CONFIRMATION]
	// (directory_entry >> 12) * PAGE_SIZE  or page_table_entry & 0xFFFFF000
	uint32 page_table_physical_address = (directory_entry >> 12) * PAGE_SIZE;
	cprintf("page_table_physical_address is : %x\n" ,page_table_physical_address) ;
	//=====================================================================
	// 7-page physical address [need CONFIRMATION]
	// (table entry >> 12) * PAGE_SIZE
	uint32 page_physical_address = (page_table_entry >> 12 ) * PAGE_SIZE;
	cprintf("page_physical_address is : %x\n" ,page_physical_address) ;
	//=====================================================================
	// 8-present status of page_table (directory entry permissions)
	int present_bit = directory_entry & PERM_PRESENT ;
	if (present_bit) { cprintf("page table is present\n") ;}
	else{cprintf("page table is not present\n");}
	//=====================================================================
	// 9-used bit of the page (table entry permissions)
	int used_bit = page_table_entry & PERM_USER ;
	if (used_bit) {cprintf("page is used\n") ;}
	else{cprintf("page is not used\n") ;}
	//=====================================================================
	// 10-frame number of page table (directory entry)
	int fram_number_of_page_table = directory_entry >> 12 ;
	cprintf("Frame number of page table : %d\n",fram_number_of_page_table) ;
	//=====================================================================
	// 11-frame number of page (table entry)
	int frame_number_of_page = page_table_entry >> 12 ;
	cprintf("Frame number of page : %d\n",frame_number_of_page) ;
	//=====================================================================
	return 0 ;
}