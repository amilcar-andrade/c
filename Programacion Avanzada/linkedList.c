#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo{
	int data;
	struct nodo * sig;
}nodo_t;

nodo_t* inserta(nodo_t *lst, int x){
	nodo_t * nuevo = malloc(sizeof(nodo_t));
	nuevo -> data = x;
	nuevo -> sig = lst;
	return nuevo; // devuelve el nuevo valor de inicio
}

void imprime(nodo_t*lst){
	printf("[");
	int primero = true;
	
	while (lst) { //si no esta apuntando a NULL, acaba cuando el ultimo elemento apunta al NULL
		if (primero){
			primero = false;
		}else {
			printf(", ");
		}
		printf("%i",lst -> data);
		lst = lst ->sig; //avanzas al sigueinete nodo
	}
	printf("]\n");
}

size_t longitud(nodo_t*lst){
	size_t tam = 0;
	while (lst) {
		tam++;
		lst = lst -> sig;		
	}
	return tam;
}

void libera(nodo_t * lst){
		while (lst) {
			nodo_t * p = lst;
			lst = lst -> sig;
			free(p);
			p = NULL;
		}
}

void duplica(nodo_t * lst){	
while (lst) {
	lst -> sig = inserta(lst->sig,lst->data); //pido lo que tiene el primer elemento y lo agrego despues de el.
	lst =lst->sig->sig; //me adealnto dos lugares porque ya tendria el primer elemento repetido.
}
}

int main(){
	int tam =0;
	nodo_t * inicio = NULL;
	duplica(inicio);
	imprime(inicio);
	tam = longitud(inicio);
	printf("%i\n", tam);	
	inicio = inserta(inicio,5);
	inicio = inserta(inicio,6);
	inicio = inserta(inicio,7);
	duplica(inicio);
	imprime(inicio);
	tam = longitud(inicio);
	printf("%i\n", tam);
	libera(inicio);
	inicio=NULL;
	return 0;
}
