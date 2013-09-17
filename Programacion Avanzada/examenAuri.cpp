#include<stdio.h>
int main()
{
	int x = 4;
	printf("x lives at %p\n", &x);
	int *address_of_x;
	
	
	address_of_x = x;
	printf("Valor de x %i\n", address_of_x);
	
	return 0;
}