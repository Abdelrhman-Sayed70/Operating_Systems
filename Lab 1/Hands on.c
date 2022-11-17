//Lab1.Hnads.On
//=============
int command_version(int number_of_arguments, char **arguments)
{
	//(version)
	cprintf("This is FOS version 1\n") ;
	return 0 ;
}
int command_add(int number_of_arguments, char **arguments)
{
	// (add)(num1)(num2)
	int n1 = strtol(arguments[1],NULL,10) ;
	int n2 = strtol(arguments[2],NULL,10) ;
	int sum = n1+n2 ;
	cprintf("sum of 2 numbers is : %d\n", sum) ;
	return 0;
}
int command_add_range(int number_of_arguments, char **arguments)
{
	int sum = 0 ;
	for(int i=1 ;i<number_of_arguments ;i++) {
		int n = strtol(arguments[i],NULL,10) ;
		sum+=n ;
	}
	cprintf("sum of values is : %d\n" ,sum) ;
	return 0;
}