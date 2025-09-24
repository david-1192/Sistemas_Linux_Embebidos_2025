#include "stdio.h"

int main(int argc, char *argv[]){
    if (argc==1)
        printf("Hello world!!\n\r");
    if (argc==2)
        printf("Hello %s!!\n\r", argv[1]);
    if (argc>2)
        printf("This program requires zero or one argument.\n\r !");
    return 0;
}