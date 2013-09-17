#include<stdio.h>

int main(){
	double n,sum=0;
	double temp = 1;
	int i = 1;
	int j = 1;
	int k = 1;
	printf("\n Ingresa un numero: ");
	scanf("%lf",&n);
	int sizeArreglo = (int) n;
	int arreglo[sizeArreglo];
	int contador = sizeArreglo;
	
	for(i;i<=n;i++)
	{//Relleno el arreglo
		arreglo[i] = i;
	}
	
	
	for (k; k<=sizeArreglo; k++){
		
	for(j;j<=contador;j++)
	{
		temp = temp * arreglo[j];
	}
		printf("\n Factorial %g", temp);
		contador = contador - 1;
		printf("\n Contador %i", contador);
		sum = (1/temp) + sum;
		printf("\n Suma %g", sum);
		temp = 1;
		j = 1;
	}
	
	sum = sum +1;
	
	printf("\n La exponencial es:  %g\n", sum);
	return 0;
}