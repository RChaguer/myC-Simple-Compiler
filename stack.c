#include <stdio.h>
#include "stack.h"



void stack__init(){
    printf("#define SIZE 100 \n");
    printf( "int stack[SIZE];\n"); 
    printf( "int * sp = stack;\n");
    printf( "int * fp = stack;\n");
}


void stack__save(){
    printf("*sp = (int) fp;\n");
    printf( "sp = sp + 1;\n");
}

void stack__new(){
    printf("fp = sp;\n");
    printf( "sp = sp + 1;\n");
}

void stack__push(){
    printf("sp = sp + 1;\n");
}

void stack__reset(){
    printf("sp = fp - 1;\n");
    printf( "fp = *sp; \n");
}

void stack__return(attribute x){
    printf("*fp = *(fp + %d);\n", x->reg_number);
}

void stack__push_param(attribute x){
    printf("*sp = *(*(fp-1) + %d); //*(fp-1) = ancien fp \n",x->reg_number);
    stack__push();
}

void stack__push_numi(attribute x){
    printf("*sp = %d;\n",x->int_val);
    stack__push();
}