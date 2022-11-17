![Function](https://user-images.githubusercontent.com/99830416/202505203-b87f7d79-115d-4cdb-8830-a3da4514e8b9.png)
## Code : 
```c
int *mypointer = (int *)(0xF1000000) ; // to avoid override for each time you create new array
int command_create_int_array(int number_of_arguments, char **arguments)
{
	// (create_int_array)(size)
	int size = strtol(arguments[1] ,NULL,10);
	cprintf("start virtual address of the allocated array is : %x\n" , mypointer) ;
	for(int i=0 ;i<size ;i++) {
		char arr[2] ;
		readline("Enter value : " ,arr) ;
		int val = strtol(arr,NULL,10) ;
		*mypointer = val ;
		mypointer++ ;
	}
	return 0;
}
```
