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

/*
void cond_free2(attribute x, attribute y)
{
  if (!x->permanent)
  {
    free(x);
  }
  if (!y->permanent)
  {
    free(y);
  }
}*/

int new_reg_num()
{
  return reg_count++;
}

int new_label()
{
  return label_count++;
}

//PRINTER


void write_type(attribute r)
{
  if (r->type_val == INT)
    printf("int ");
  else if (r->type_val == FLOAT)
    printf("float ");
}
/*
void write_stars(attribute r)
{
  for (int i = 0; i < r->stars; i++)
  {
    printf("*");
  }
}*/

void write_func(attribute r)
{
  printf("void call_%s(){\n", r->name);
}

void write_aff(attribute r, attribute s)
{
  printf("*(fp + %d) = *(fp + %d);\n",r->reg_number, s->reg_number);
}

void write_aff_app(attribute r)
{
  printf("*sp = *(sp + 1);\n");
}

void write_aff_p(attribute r, attribute s, int reg_num)
{
  printf("ri%d = *ri%d;\n", reg_num, s->reg_number);
  printf("%s = *ri%d;\n", r->name, s->reg_number);
}




attribute plus_attribute(attribute x, attribute y) {
  attribute r = new_attribute();
  r->reg_number=get_next_register();
  /* unconditionally adding integer values */
  printf("*sp = *(fp + %d) + *(fp + %d);\n", x->reg_number, y->reg_number);
  stack__push();
  return r;
};

attribute mult_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val * y -> int_val;
  return r;
};

attribute minus_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val - y -> int_val;
  return r;
};

attribute div_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val % y -> int_val;
  return r;
};

attribute neg_attribute(attribute x){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = -(x -> int_val);
  return r;
};

attribute bool_attribute(attribute x, char *op, attribute y)
{
  attribute r = new_attribute();
  r->reg_number = new_reg_num();
  r->type_val = INT;
  write_type(r);
  printf("ri%d;\n", r->reg_number);
  printf("ri%d = ri%d %s ri%d;\n", r->reg_number, x->reg_number, op, y->reg_number);
  return r;
};
