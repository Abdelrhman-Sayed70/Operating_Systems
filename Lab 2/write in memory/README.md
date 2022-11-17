![function 1 ](https://user-images.githubusercontent.com/99830416/202487455-f9fb8fa0-586f-4079-b9e3-9a2d7f4c1709.png)
## Code : 
```c
int command_writemem(int number_of_arguments, char **arguments)
{
	// (wum)(char)(physical address)
	// any pointer in code should point to virtual memory
	// address passed here is physical address so we should convert it to virtual address
	// virtual address  = physical address + KERNEL_BASE
	// physical_address = virtual_address - KERNEL_BASE
	int physical_address = strtol(arguments[2],NULL,16) ;
	int virtual_address = physical_address + KERNEL_BASE ;
	char *ptr = (char *) virtual_address ;
	*ptr = arguments[1][0];
	return 0;
}
```
