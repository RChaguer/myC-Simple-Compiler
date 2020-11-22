#include <stdio.h>
#define SIZE 100 
void * stack[SIZE]; 
void ** sp = stack+1;
void ** fp = stack;

void call_f(){
    *sp = (void *) 6;
    sp = sp + 1;
    *fp = *(fp + 2);
}   

int main(){
    sp = sp + 1; // a 1
    *sp = (void *) 6; // 6 2
    sp = sp + 1;
    *sp = fp;
    sp = sp + 1;
    fp = sp;
    sp = sp + 1;
    *sp = *( (void **) *(fp-1) + 2); //*(fp-1) = ancien fp
    sp = sp + 1;
    call_f();
    sp = fp - 1;
    fp = *sp;
    
    *sp = *(sp + 1);
    sp = sp + 1; 

    *sp = (void *) 1; //4
    sp = sp + 1;
    *sp = (void *) ((long) *(fp + 3) + (long) *(fp + 4));
    sp = sp + 1;
    *(fp + 1) = *(fp + 5);
    printf("%ld\n",(long)*(fp + 1));
    return 0;
}