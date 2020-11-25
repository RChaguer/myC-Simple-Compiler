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
  r->stars_number = 0;
  return r;
};

int new_label()
{
  return label_count++;
}

//PRINTER



void print_func(attribute r)
{
  if(strcmp(r->name,"main"))
    printf("void call_%s()\n", r->name);
  else  
    printf("int main()\n");
}

void print_affect(attribute r, attribute s)
{
  if(r->stars_number && s->stars_number && r->stars_number !=s->stars_number){
    fprintf(stderr,"cannot convert types in assignments\n");
      exit(-1);
  }
  if(!r->stars_number && s->stars_number){
    fprintf(stderr,"cannot convert a pointer to simple type in assignment\n");
      exit(-1);
  }
  if(r->type_val != s->type_val){
    fprintf(stderr,"assignments of variable with differnet type\n");
      exit(-1);
  }
  printf("*(fp + %d) = *(fp + %d);\n",r->reg_number, s->reg_number);
}

void print_affect_app()
{
  printf("*sp = *(sp + 1);\n");
}

void print_affect_p(attribute r, attribute s)
{
  if(r->stars_number && s->stars_number && r->stars_number != s->stars_number -1){
    fprintf(stderr,"cannot convert types in assignments\n");
      exit(-1);
  }

  if(r->type_val != s->type_val){
    fprintf(stderr,"assignments of variable with differnet type\n");
      exit(-1);
  }
  printf("*((void **) *(fp+%d)) = *(fp + %d);\n", r->reg_number, s->reg_number);
}

void print_stars(attribute r)
{
  for (int i = 0; i < r->stars_number; i++)
  {
    printf("*\n");
  }
  printf("%d*\n",r->stars_number);
}

attribute plus_attribute(attribute x, attribute y) {
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  if (x->type_val == y->type_val) {
    if(x->stars_number && y->stars_number){
      fprintf(stderr,"Forbiden operation: pointer + pointer\n");
      exit(-1);
    }
  }
  else {
    if(x->stars_number && y->stars_number) {
      fprintf(stderr,"Forbiden operation: pointer + pointer\n");
      exit(-1);
    }
    else if(x->type_val != INT && !x->stars_number && y->stars_number){
      fprintf(stderr,"Forbiden operation: not int + pointer\n");
      exit(-1);
    }

    else if(y->type_val != INT && !y->stars_number && x->stars_number){
      fprintf(stderr,"Forbiden operation: pointer + not int\n");
      exit(-1);
    }

  }
  printf("*sp = (void *)((long) *(fp + %d) + (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute mult_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  printf("*sp = (void *)((long) *(fp + %d) * (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute minus_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
    if(x->stars_number && y->stars_number && x->stars_number != y->stars_number){
    fprintf(stderr,"Forbiden operation\n");
    exit(-1);
  }
  else if(!x->stars_number && y->stars_number){
    fprintf(stderr,"Forbiden operation\n");
    exit(-1);
  }
  else if(y->type_val != INT && !y->stars_number && x->stars_number){
    fprintf(stderr,"Forbiden operation: pointer - not int\n");
    exit(-1);
  }
  printf("*sp = (void *)((long) *(fp + %d) - (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute div_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  printf("*sp = (void *)((long) *(fp + %d) / (long)*(fp + %d));\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute neg_attribute(attribute x){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
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

attribute not_attribute(attribute x){
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  printf("*sp = (void *)(!*(fp + %d)) ;\n", x->reg_number);
  stack__push();
  return r;
};