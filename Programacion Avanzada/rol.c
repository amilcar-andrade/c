//Amilcar Andrade Garcia 1163951
#include <stdio.h>

unsigned rol(unsigned x, unsigned n);

int main(void) {
	printf("0x%08X\n", rol(0x80000002, 2));
	printf("0x%08X\n", rol(0xECAFEBAB, 36)); 
	printf("0x%08X\n", rol(-5, 29));
	printf("0x%08X\n", rol(0xDEADBEAF, -48));
	printf("0x%08X\n", rol(0x587D6758, 25));                
	return 0;
}


unsigned rol(unsigned x, unsigned n){
	unsigned x2; 
	n = n&31; 
	x2 = x >> (32 - n); 	
	x = x << n; 
	x =x|x2; 
	return x;
}
