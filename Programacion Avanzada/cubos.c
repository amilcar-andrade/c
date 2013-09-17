#include <math.h>
#include <stdio.h>	// for printf() call
#include <string.h>
#include <stdlib.h>

int main(){ 
	int i,j,k,suma,condicion;
	char buff[4];
	char buff1[4];
	char buff2[4];

	
	for (i=0; i<=9; i++) {
		for (j=0; j<=9; j++) {
			for (k=0; k<=9; k++) {

				suma = pow(i,3)+pow(j,3)+pow(k,3);
				sprintf( buff, "%d", i );
				sprintf( buff1, "%d", j);
				sprintf( buff2, "%d", k);
				strcat(buff,buff1);
				strcat(buff,buff2);
				condicion = atoi(buff);
				if (suma==condicion) {
					printf("Es un cubo narcisita %s\n",buff); 
			
			}
			
		}
	}
		
	}
		 
	 return 0; 
}