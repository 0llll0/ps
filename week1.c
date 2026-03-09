#include <stdio.h>

int main() {
    

    int size;
    int stars, blank1, blank2;
    int i, j;
for(j=0;j<10;j++){
    for(i=0; i<10; i++){

        //j=>
        //
        if( i == j || i == 9 - j){
            printf("*");

        } else {
        printf(" ");
        }
        if(i=9){
            printf("\n");
        }
    }
    return 0;
}
}