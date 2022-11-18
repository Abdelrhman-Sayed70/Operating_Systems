![Function](https://user-images.githubusercontent.com/99830416/202568553-951fa658-1bad-4cc0-8ab4-701bf221f0e0.png)
## Code : 
```c
uint32 *ptr_page_table = NULL;
get_page_table(ptr_page_directory, KERNEL_BASE, &ptr_page_table);
if (ptr_page_table  != NULL)
{
	ptr_page_table[PTX(KERNEL_BASE)] = 
	ptr_page_table[PTX(KERNEL_BASE)] & (~PERM_PRESENT);
}
```
