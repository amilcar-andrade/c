/*
Autores: 
Julio César Rodríguez Mejía 1164941
Amilcar Andrade García  1163951
Decodificación de UTF-8

leemos caracter por caracter y procesamos su valor binario
tenemos 5 casos:

Codigos de control, no imprimibles
numero binario menor a 0x20, sustituir por un punto

Codificados:
checar primer bit 		= 0		caracteres de 1 byte
checar primeros 3 bits 	= 110	caracteres de 2 bytes
checar primeros 4 bits	= 1110 	caracteres de 3 bytes
checar primeros 5 bits	= 11110	caracteres de 4 bytes

la verificación se hace con corrimientos

Para obtener los valores unicode se concatenan bits
haciendo corrimientos y sumas (or) 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
	unsigned int c = 0;
	unsigned int counter = 0;
	unsigned int counterb = 0;
	unsigned int unicode = 0;
	unsigned char g[5] = "0000";
	
	//el usuario no indica el archivo:
	if(argc != 2){
		printf("Se debe indicar el nombre del archivo\n");
		return 0;
	}
	
	//ejecución normal del programa
	//abrir el archivo de lectura
	FILE *text = fopen(argv[1], "r");
	
	//imprimer encabezados de la tabla
	printf("=========================================\n");
	printf("index\tunicode\tutf-8\t\tglyph\n");
	printf("=========================================\n");
	
	//leer los caracteres, esperar el end of file
	while(c != EOF){
		unicode = 0;
		c = fgetc(text);
		//checar el tipo de caracter
		//menores que 0x20 sustituir por un punto
		if(c<0x20){
			unicode = c;
			g[0] = 0x2e;
			g[1] = 0;
			printf("%04X\t %06x\t %02x\t\t %s\n",
			 		counter, c, c, g);
			counter+=1;
			counterb+=1;
			continue;
		}
		
		//caracteres de 1 byte
		if (!(c>>7)){
			g[0] = c;
			g[1] = 0;
			unicode|=c&0x7F;
			//printf("%05x\n", unicode);
			printf("%04X\t %06x\t %02x\t\t %s\n",
					counter, unicode, c, g);
			counter+=1;
			counterb+=1;
			continue;
		}
		
		//caracteres de 2 bytes
		if((c>>5)==0x06){
			g[0]=c;
			g[1]=fgetc(text);
			g[2]=0;
			unicode|= g[0]&0x1F;
			unicode<<=6;
			unicode|= g[1]&0x3F;
			//printf("%05x\n", unicode); 
			printf("%04X\t %06x\t %02x %02x\t\t %s\n",
					counter, unicode, g[0], g[1], g);
			counter+=1;
			counterb+=2;
			continue;
		}
		
		//caracteres de 3 bytes
		if((c>>4)==0x0E){
			g[0]=c;
			g[1]=fgetc(text);
			g[2]=fgetc(text);
			g[3]=0;
			unicode|= g[0]&0x0F;
			unicode<<=6;
			unicode|= g[1]&0x3F;
			unicode<<=6;
			unicode|= g[2]&0x3F;
			//printf("%05x", unicode);
			printf("%04X\t %06x\t %02x %02x %02x\t %s\n",
					counter, unicode, g[0], g[1], g[2], g);
			counter+=1;
			counterb+=3;
			continue;
		}	 
		
		//caracteres de 4 bytes
		if((c>>3)==0x1E){
			g[0]=c;
			g[1]=fgetc(text);
			g[2]=fgetc(text);
			g[3]=fgetc(text);
			g[4]=0;
			unicode|= g[0]&0x07;
			unicode<<=6;
			unicode|= g[1]&0x3F;
			unicode<<=6;
			unicode|= g[2]&0x3F;
			unicode<<=6;
			unicode|= g[3]&0x3F;
			printf("%04X\t %06x\t %02x %02x %02x %02x\t %s\n",
					counter, unicode, g[0], g[1], g[2], g[3], g);
			counter+=1;
			counterb+=4;
			continue;
		}	 
	}
	
	printf("=========================================\n");
	printf("Número total de caracteres: %d\n", counter);
	printf("Número total de bytes: %d\n", counterb);
	fclose(text);
	return 0;
} 
