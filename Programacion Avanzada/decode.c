//1166848
//Ivan Haecker
#include <stdio.h>
#include <string.h>

int main (void) {
	printf("======================================\n");
	printf("indx\t unicode\t utf-8\t\t glyph\n");
	printf("======================================\n");
	printf("%s\n", "\xe2\x9d\xa4");
	
	char cadena [5];
	int indx = 0;
	char* n = "ñ";
	char* r = n;
	char* p = n;
	
	char a;
	char b;
	char c;
	printf("%04X\t ",indx, (unsigned char)*n);
	
	while (*n){
		if ((*n & 192) == 192){
		a = (unsigned char)*r;
		b = (unsigned char)*r++;
		c = (unsigned char)*r++;		
		printf("a %02x b %02x c %02x", a, b, c);
		a = (a & 28) >>2;
		b = ((b & 3) <<2) | ((c & 48) >>4); 
		c = (c & 15);
		
		printf("a %d b %d c %d", a, b, c);
		/*
		printf("%d", (unsigned char)*r & );
		printf("u%d", (unsigned char)*++r);
		printf("u%d", (((unsigned char)*r++) & 28)>>2 );
		printf("b%d ", ((unsigned char)*r) & 3);
		printf("%d ", ((unsigned char)*r++) & 48);
		printf("%02x ", ((unsigned char)*r) & 15); */
		}
		if ((*n & 224) == 224){
		}
		if ((*n & 240) == 240){
		}
		indx ++;
		printf("%02x ", (unsigned char)*n++);
	}
	printf("%c\n",(unsigned char)*r);
	printf("%s\n", "\xe2\x9d\xa4");	
			/*
			while (x != 5){
			printf("%04X\t %06X\t utf\t\t %c\n", indx, n, n );
			x = x+1;
			indx ++;
			n = getchar();
			
			
			
			}*/
			printf("Se acabo\n");
			return 0;		
	}
