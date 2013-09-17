#include <stdio.h>
#include <string.h>


char * reversa (char *s) {
 int lenght = strlen(s);
 char temp = (*s);
 int i = lenght-1;
 for (i = lenght-1; i>0; i--){
  strcpy(s,s+1);
  *(s+1) = temp;
  temp = (*s);
 }
 return s;
}

int main (){
 char cadena[] = "hola";
 printf("Antes: %s\n", cadena);
 reversa(cadena);
 printf("Despúes: %s\n", cadena);
 return 0;
}
