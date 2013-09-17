#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

#define MAX_SIZE_NUMSTR 128

/*
 * Lee el siguiente número de file como una secuencia de dígitos. Devuelve
 * el número leído o -1 si se llegó al final del archivo.
 */
static int next_num(FILE* file) {
    int c;
    
    do {
        c = fgetc(file);
        if (c == '#') {
            while ((c = fgetc(file)) != '\n' && c != EOF);
        }         
    } while (!isdigit(c) && c != EOF);
    
    if (c == EOF) return -1;
    
    char numstr[MAX_SIZE_NUMSTR];
    char* charp = numstr;
    *charp++ = c;
    
    while(isdigit(c = fgetc(file)) && charp < (numstr + MAX_SIZE_NUMSTR - 1)) {
        *charp++ = c;
    }
    
    *charp = '\0';
    
    return strtol(numstr, NULL, 10);    
}

/*****************PPM OPEN************************/
error_code_t ppm_open(const char* file_name, ppm_t* ppm_ptr) {
    FILE* file;
    
    file = fopen(file_name, "r");
    if (!file) {
        return UNABLE_TO_OPEN;
    }
    
    int byte1 = fgetc(file);
    int byte2 = fgetc(file);
    if (byte1 != 'P' || byte2 != '3') {
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
    
    ppm_ptr -> width = width;
    ppm_ptr -> height = height;
    ppm_ptr -> max_value = max_value;
    
    int total_pix = width * height;    
    ppm_ptr -> pixels = malloc(total_pix * sizeof(rgb_t));
    
    if (!(ppm_ptr -> pixels)) {
        fclose(file);
        return NO_MEMORY;
    }
        
    for (int i = 0; i < total_pix; i++) {
        ppm_ptr -> pixels[i].red = next_num(file);
        ppm_ptr -> pixels[i].green = next_num(file);
        ppm_ptr -> pixels[i].blue = next_num(file);
        if (ppm_ptr -> pixels[i].red == -1 ||
            ppm_ptr -> pixels[i].green == -1 ||
            ppm_ptr -> pixels[i].blue == -1) {
            fclose(file);
            free(ppm_ptr -> pixels);
            ppm_ptr -> pixels = NULL;            
            return INVALID_FORMAT;
        }
    }
    
    fclose(file);    
    return OK;
}

void ppm_dispose(ppm_t* ppm_ptr) {
    if (ppm_ptr -> pixels) {
        free(ppm_ptr -> pixels);
        ppm_ptr -> pixels = NULL;
    }    
}

error_code_t ppm_save(const char* file_name, ppm_t* ppm_ptr) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        return UNABLE_TO_OPEN;
    }
    fprintf(file, "P3\n");
    fprintf(file, "# CREATOR: PPM Library\n");
    fprintf(file, "%d %d %d\n", 
        ppm_ptr -> width, 
        ppm_ptr -> height, 
        ppm_ptr -> max_value);
    int total_pix = ppm_ptr -> width * ppm_ptr -> height;
    for (int i = 0; i < total_pix; i++) {
        fprintf(file, "%d %d %d\n",
            ppm_ptr -> pixels[i].red,
            ppm_ptr -> pixels[i].green,
            ppm_ptr -> pixels[i].blue);
    }
    fclose(file);
    return OK;    
}


/*****************COMPRESS FUNCTION*********************/
error_code_t ppm_save_c(const char* file_name, ppm_t* ppm_ptr) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        return UNABLE_TO_OPEN;
    }
    fprintf(file, "P3\n");
    fprintf(file, "# CREATOR: PPM Library, COMPRESSED\n");
    fprintf(file, "%d %d %d\n", 
        (ppm_ptr -> width)/2, 
        (ppm_ptr -> height)/2, 
        ppm_ptr -> max_value);
    int total_pix = (ppm_ptr -> width * ppm_ptr -> height)/4;
    
    int index = 0;
    int index_c = 0;
    //printf("Imagen comprimida:\n");
    for (int i = 0; i < ppm_ptr->height; i++) {
        if(!(i%2)){
        //printf("\nr%d:\t", i);
        fprintf(file, "\n");
        }
        for (int j = 0; j < ppm_ptr->width; j++) {
        	if(!(j%2) && !(i%2)){
        	//printf("%d %d %d\t", ppm_data.pixels[index].red,
        	//ppm_data.pixels[index].blue,
        	//ppm_data.pixels[index].green);
        	fprintf(file, "%d %d %d\t",
            ppm_ptr->pixels[index].red,
            ppm_ptr->pixels[index].green,
            ppm_ptr->pixels[index].blue);
        	index_c++;
        	}
        	index++;
        }
    }
    fclose(file);
    return OK;    
}


