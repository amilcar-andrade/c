#include <stdio.h>

int raro(int x){	
	long long a[2];
	a[0] = x;
	a[1] = x;
	return 0;
}

int main(){
	puts("Primera Linea");
	int r = raro(5);
	puts("Segunda Linea");
	puts("Tercera Linea");
	return 0;
}
