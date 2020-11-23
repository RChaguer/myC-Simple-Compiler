#include <stdio.h>
#define SIZE 100 
void * stack[SIZE];
void ** sp = stack+1;
void ** fp = stack;
void call_f(){
    *sp =(void*) 6;
    sp = sp + 1;
    *fp = *(fp + 2);
}

int main(){
    sp = sp + 1;
    *sp =(void*) 6;
    sp = sp + 1;
    *sp = (void*) fp;
    sp = sp + 1;
    fp = sp;
    sp = sp + 1;
    *sp = *((void**)*(fp-1) + 2); //*(fp-1) = ancien fp
    sp = sp + 1;
    call_f();
    sp = fp - 1;
    fp = *sp;
    *sp = *(sp + 1);
    sp = sp + 1;
    *(fp + 1) = *(fp + 3);
    *sp =(void*) 6;
    sp = sp + 1;
    *sp = (void *) (long)(*(fp + 1) == *(fp + 4));

     printf("%ld\n",(long)*sp);
    return 0;
}