/* 
 * Usando listas encadenadas.
 * Ejemplo visto en clase.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
    int data;
    struct nodo * sig;
} nodo_t;

nodo_t * inserta(nodo_t * lst, int x) {
    nodo_t * nuevo = malloc(sizeof(nodo_t));
    nuevo -> data = x;
    nuevo -> sig = lst;
    return nuevo;
}

void imprime(nodo_t * lst) {
    printf("[");
    bool primero = true;
    while (lst) {
        if (primero) {
            primero = false;
        } else {
            printf(", ");
        }
        printf("%i", lst -> data);
        lst = lst -> sig;
    }
    printf("]\n");
}

void libera(nodo_t * lst) {
    while (lst) {
        nodo_t * p = lst;
        lst = lst -> sig;
        free(p);
        p = NULL;
    }
}

size_t longitud(nodo_t * lst) {
    size_t tam = 0;
    while (lst) {
        tam++;
        lst = lst -> sig;
    }
    return tam;
}

void duplica(nodo_t * lst) {
    while (lst) {
        lst -> sig = inserta(lst -> sig, lst -> data);
        lst = lst -> sig -> sig;
    }     
}

void mapea(struct nodo* lst, fun f) {
    while (lst) {
        lst -> info = f(lst -> info);
        lst = lst -> sig;
    }
}


int main() {
    nodo_t * inicio = NULL;
    duplica(inicio);
    imprime(inicio);
    printf("%lu\n", longitud(inicio));
    inicio = inserta(inicio, 5);
    imprime(inicio);
    inicio = inserta(inicio, 4);
    inicio = inserta(inicio, 3);
    duplica(inicio);
    imprime(inicio);
    printf("%lu\n", longitud(inicio));
    libera(inicio);
    inicio = NULL;    
    return 0;
}
