//Amilcar Andrade Garcia 1163951
//Given that 100! < 100^100 = 10^200, we know that 100! has less than 200 digits.

#include <stdio.h>
#define Limite 199
int main(void){
	int n=0;
	int i=0;
	int m=0;
	int num[200]; //creo un arreglo de 200 casillas
	int total= 0;
	int res=0;
	int fact = 0;
	int j = 0;
	scanf("%d", &n);
	int array[n]; //creas el arreglo dependiendo del numero que te llegue o leeas
	m = n; //lo asginas a la variable m, para tener el mismo valor
	for (i = 0; i != n; i++){
		scanf("%d",&m);
		array[i] = m;} //metes los valores al arreglo
	
	for(i = 0; i!=n; i++){
		for(j=0; j < Limite+1; j++){ //lo recorres hasta el limite +1 ya que nunca pasas de este rango
		num[j] = 0;}
		j = Limite;		
		num[Limite] = 1;	
		
		for(fact = 2;fact <= array[i]; fact++){  
			while(j>0){						
				total = num[j]*fact+res; 	
				res = 0;
				if(total>9){
					num[j] = total%10; //divides el numero si es de 2 digitos
					res = total/10;
				}else{ 
					num[j]=total;}
				j--;}
			res = 0;
			total = 0;
			j = Limite;}
		for(j=0;j < Limite+1;j++){      
			if(num[j] !=0 | fact == 1){
				fact << num[j];
				fact = 1;
				printf("%d",num[j]);}}
		printf("\n");}
	return 0;}
