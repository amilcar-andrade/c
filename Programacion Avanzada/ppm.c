#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include <ctype.h>
#define MAX_SIZE_NUMSTR 128;

/*
 Lee el siguiente numero de file como una secuencia de digitos. Devuelve el numero
 leido o -1 si se llego al final de archivo
 */

static int next_num(FILE* file){
	int c;
	
	do {
		c = fgetc(file);
		if (c =='#') {
			while ((c = fgetc(file)) != '\n' && c != EOF);
			}
	}while (!isdigit(c) && c != EOF);
	
	if (c==EOF) {
		return -1;
	}
	
	char numstr[MAX_SIZE_NUMSTR];
	char* charp = numstr; //esta apuntando al primer caracter del arreglo el char pointer
	*charp++ = c;
	
	while (isdigit(c=fgetc(file)) && charp < (numstr+ (MAX_SIZE_NUMSTR-1))) {
		*charp++ = c;
	}
	*charp = '\0';
	return strol(numstr,NULL,10); //Base 10
	
	
}

error_code_t ppm_open(const char* file_name, ppm_t* ppm_ptr){ //ptr = pointer
	FILE *file;
	file = fopen(file_name,"r");
	if(!file){
		return FILE_UNABLE_TO_OPEN;
	}
	int byte1 = fgetc(file);//primer caracter del FIle
	int byte2 = fgetc(file);//segundo caracter del FILE
	if(byte1 != 'P' || byte2 != '3'){
		fclose(file);
		return INVALID_FORMAT;
	}
	
	int width = next_num(file);
	int height = next_num(file);
	int max_value = next_num(file);
	
	if (width == -1 || height == -1 || max_value == -1) {
		fclose(file);
		return INVALID_FORMAT;
	}
	ppm_ptr -> width = next_num(file);
	ppm_ptr -> height = next_num(file);
	ppm_ptr -> max_value = next_num(file);

	return OK;
} 
