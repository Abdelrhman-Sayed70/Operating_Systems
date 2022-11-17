int command_share_page(int number_of_arguments, char **arguments)
{
	//TODO: LAB3 Example: fill this function. corresponding command name is "shr"
	//Comment the following line
	//panic("Function is not implemented yet!");
	
	// share one page to another
	// (shr)(VA1)(VA2)
	uint32 va1 = strtol(arguments[1],NULL,16) ;
	uint32 va2 = strtol(arguments[2],NULL,16) ;

   	uint32 *ptr_page_table1 = NULL;
	uint32 *ptr_page_table2 = NULL;
	get_page_table(ptr_page_directory,va1,&ptr_page_table1) ;
	get_page_table(ptr_page_directory,va2,&ptr_page_table2) ;

	if (ptr_page_table1 != NULL){
		if (ptr_page_table2 == NULL) {
			ptr_page_table2 = create_page_table(ptr_page_directory ,va2) ;
		}
		ptr_page_table2[PTX(va2)] = ptr_page_table1[PTX(va1)];
	}

	return 0;
	// NOTE THIS FUNCTION IMPLEMENTED IN PROJECT TEMPLATE 2 NOT IN LABS TEMPLATE
}
