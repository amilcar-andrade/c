#include<stdio.h>
int main()
{
	int n,i;
	puts("Enter a Number:");
	scanf("%d",&n);
	printf("\n\nFactors of %d is:\n",n);
	
	if(n <= 1 ){
		printf("Error: No se pueden calcular los factores primos de %i\n", n);		
	}else{
	for(i=2;i<n;i++)
	{
		if(n%i==0)
			printf("%d, ",i);
	}
	}
	return 0;
}


