#include <stdio.h>
 
int main()
{
   signed int n = 0;
   int c = 2;
   signed int cuenta = 0;
   
	
   for (n=2; n<=97; n++) {
 
   for ( c = 2 ; c <= n - 1 ; c++ )
   {
      if ( n%c == 0 )
      {
	cuenta = cuenta - n;
	 break;
      }
   }
	   
   if ( c == n )
      printf("%d ", n);
	   cuenta = cuenta + n;
	  	   
	   
   }
	printf("\n");
	printf("%i\n", cuenta);

 
   return 0;
}
