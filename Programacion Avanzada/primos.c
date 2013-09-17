#include <stdio.h>
int main()
{

		signed int n = 0;
		signed int c = 2;
		signed int cuenta = 0;
		signed int numero;
	    signed int zero = 0;
	
    puts("Dame un número entero:");
    scanf("%i", &numero);

	if(numero <= zero ){
		printf("La suma de los números primos menores o iguales a %i es: 0 ", 0);

	}else {
		for (n=2; n<=numero; n++) {
			
			for ( c = 2 ; c <= n - 1 ; c++ )
			{
				if ( n%c == 0 )
				{
					break;
				}
			}
		
			if ( c == n ){
			cuenta = cuenta + n;
			}
		}
		printf("La suma de los números primos menores o iguales a %i es: " ,numero);
		printf("%i\n", cuenta);
		
	}

	
	return 0;	
}


