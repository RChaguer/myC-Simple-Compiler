#include "Attribute.h"
#include "Table_des_symboles.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int reg_count = 0;
int label_count = 0;

attribute new_attribute () {
  attribute r;
  r  = malloc (sizeof (struct ATTRIBUTE));
  r->name = NULL;
  return r;
};



int new_reg_num()
{
  return reg_count++;
}

int new_label()
{
  return label_count++;
}

//PRINTER



void print_func(attribute r)
{
  if(strcmp(r->name,"main"))
    printf("void call_%s(){\n", r->name);
  else  
    printf("int main(){\n");
}

void print_affect(attribute r, attribute s)
{
  printf("*(fp + %d) = *(fp + %d);\n",r->reg_number, s->reg_number);
}

void print_affect_app()
{
  printf("*sp = *(sp + 1);\n");
}

void print_affect_p(attribute r, attribute s, int reg_num)
{
  printf("ri%d = *ri%d;\n", reg_num, s->reg_number);
  printf("%s = *ri%d;\n", r->name, s->reg_number);
}




attribute plus_attribute(attribute x, attribute y) {
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = (void *)((long) *(fp + %d) + (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute mult_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = (void *)((long) *(fp + %d) * (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute minus_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = (void *)((long) *(fp + %d) - (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute div_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = (void *)((long) *(fp + %d) / (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute neg_attribute(attribute x){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = (void *)(-(long) *(fp + %d)) ;\n", x->reg_number);
  stack__push();
  return r;
};

attribute bool_attribute(attribute x, char *op, attribute y)
{
  attribute r = new_attribute();
  r->reg_number = get_next_register();
  r->type_val = INT;
  printf("*sp = (void *) (long)(*(fp + %d) %s *(fp + %d));\n", x->reg_number, op, y->reg_number);
  stack__push();
  return r;
};
