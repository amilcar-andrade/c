#include <stdio.h>
const char FILE_NAME[] = "test1.txt";
#include <stdlib.h> 

int main() {
    int             count = 0;  /* number of characters seen */
    FILE           *in_file;    /* input file */
	
    /* character or EOF flag from input */
    int            ch;
	printf("===========================================================\n");
	printf("index\t unicode\t utf-8\t\t\t glyph\n");
	printf("===========================================================\n");
    in_file = fopen(FILE_NAME, "r");
    if (in_file == NULL) {
        printf("Cannot open %s\n", FILE_NAME);
        exit(8);
    }
	
    while (1) {
        ch = fgetc(in_file);
        if (ch == EOF)
            break;
		printf("%04X\t %04X\t\t %02x\t\t\t %c\n",count,ch,ch,ch);

        ++count;
    }
	printf("\n");
	printf("===========================================================");
    printf("\nNúmero total de caracteres %d",count);
	printf("\nNúmero total de bytes %d",count);
	printf("\n");
	
    fclose(in_file);
    return (0);
}
