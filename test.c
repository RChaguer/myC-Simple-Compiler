#include <stdio.h>
#define SIZE 100     
void * stack[SIZE];  
void ** sp = stack+1;
void ** fp = stack;  

void call_fibo(){
*sp =(void*) 2;
sp = sp + 1;
*sp = (void *) (long)(*(fp + 1) < *(fp + 2));
sp = sp + 1;
if ( !*(fp + 3) ) goto l0;
*fp = *(fp + 1);
goto l1;
l0:;
*sp =(void*) 1;
sp = sp + 1;
*sp = (void *)((long) *(fp + 1) - (long)*(fp + 4));
sp = sp + 1;
*sp = (void*) fp;
sp = sp + 1;
fp = sp;
sp = sp + 1;
*sp = *((void**)*(fp-1) + 5); //*(fp-1) = ancien fp 
sp = sp + 1;
call_fibo();
sp = fp - 1;
fp = *sp;
*sp = *(sp + 1);
sp = sp + 1;
*sp =(void*) 2;
sp = sp + 1;
*sp = (void *)((long) *(fp + 1) - (long)*(fp + 7));
sp = sp + 1;
*sp = (void*) fp;
sp = sp + 1;
fp = sp;
sp = sp + 1;
*sp = *((void**)*(fp-1) + 8); //*(fp-1) = ancien fp
sp = sp + 1;
call_fibo();
sp = fp - 1;
fp = *sp;
*sp = *(sp + 1);
sp = sp + 1;
*sp = (void *)((long) *(fp + 6) + (long)*(fp + 9));
sp = sp + 1;
*fp = *(fp + 10);
l1:;
}

int main(){
sp = sp + 1;
*sp =(void*) 8;
sp = sp + 1;
*sp = (void*) fp;
sp = sp + 1;
fp = sp;
sp = sp + 1;
*sp = *((void**)*(fp-1) + 2); //*(fp-1) = ancien fp 
sp = sp + 1;
call_fibo();
sp = fp - 1;
fp = *sp;
*sp = *(sp + 1);
sp = sp + 1;
*(fp + 1) = *(fp + 3);
printf("%ld\n",(long)*(fp+1));
}