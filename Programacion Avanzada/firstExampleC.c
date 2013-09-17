#include <stdio.h>

int main(){
    unsigned char c1 = 255;
    signed char c2 = 255;
    printf("%d\n", c1);  //255
    printf("%d\n", c2); //-1
    char c3 = 255;
    printf("%d\n", c3);  //255 o -1
    
    printf("%d\n", c1+1); //256
    printf("%d\n", c2+1); //0
    
    c1++;
    c2++;
    
    printf("%d\n", c1); //0
    printf("%d\n", c2); //0
    
    unsigned int x = 0;
    printf("%u\n", sizeof(x));

    x--;
    if(x<0){
        printf("x es negativo: %u\n", x);
    }else{
        printf("x es positivo %u\n", x);
    }
    

    
    return 0;
}