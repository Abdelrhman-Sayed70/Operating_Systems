uint32 *ptr_page_table = NULL;
get_page_table(ptr_page_directory, KERNEL_BASE, &ptr_page_table);
if (ptr_page_table  != NULL)
{
	ptr_page_table[PTX(KERNEL_BASE)] = 
	ptr_page_table[PTX(KERNEL_BASE)] & (~PERM_PRESENT);
}
