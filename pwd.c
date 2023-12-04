#include "headers.h"

void pwd(){

    char str1[10000];
    printf("%s\n",getcwd(str1,sizeof(str1)));
    return;
}