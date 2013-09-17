//Amilcar Andrade Garcia 1163951
#include <stdio.h>


unsigned mul(unsigned a, unsigned b);
int main(void) {
	printf("%u\n", mul(0, 0));
	printf("%u\n", mul(1, 42));
	printf("%u\n", mul(0, 42));  
	printf("%u\n", mul(255, 255));
	printf("%u\n", mul(12345, 54321));
	printf("%u\n", mul(65535, 65535));
	printf("%u\n", mul(65536, 65536));
	return 0;
}

unsigned mul(unsigned a, unsigned b){
    unsigned cuenta;
    cuenta = 0;
    while (b > 0){	
    	if ( b & 1) { //Checo si el ultimo bit del segundo numero esta prendido para multiplicarlo y contarlo si es 0 no hago nada porque seria 0x2^n
			cuenta = cuenta + a;
		}
		a = a<< 1; //los recorro para sumar el siguiente
		b = b>> 1;  //los recorro para comparar el siguiente
    }
    return cuenta;
}
