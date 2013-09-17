#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	
	printf ("Entra tu mensaje: ");
	char buf[100];
	fgets(buf, 100, stdin); 
	printf("%s",buf);

	printf ("Entra tu numero ");
	char numArr[11], copynumArr[11];
	fgets(numArr, 11, stdin); 
	printf("Arreglo sin volteas: %s",numArr);
	puts("\n");
	

	int x =  strlen(buf);
	printf("%i",x);

	
	
		for (int i = 1; i<11; i=i+2) {
		copynumArr[i-1] = numArr[i];
		copynumArr[i] = numArr[i-1];
	}
		
	printf("Arreglo volteado %s\n",copynumArr);

	puts("\n");
	




	
	
    return 0;
}