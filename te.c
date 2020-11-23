#include <stdio.h>
#define SIZE 100 
void * stack[SIZE];
void ** sp = stack+1;
void ** fp = stack;

int main(){
     sp = sp + 1;
    *sp =(void*) 0;
    sp = sp + 1;
    *(fp + 1) = *(fp + 2);
    *sp = (void *)(long)(!*(fp + 1)) ;
    sp = sp + 1;
    if ( !*(fp + 3) ) goto l0;
    *sp =(void*) 3;
    sp = sp + 1;
    *(fp + 1) = *(fp + 4);
    *fp = *(fp + 1);
    l0:;
    printf("%ld\n",(long)*(fp+1));
    return 0;
}


