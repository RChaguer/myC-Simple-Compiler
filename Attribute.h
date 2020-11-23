/*
 *  Attribute.h
 *
 *  Created by Janin on 10/2019
 *  Copyright 2018 LaBRI. All rights reserved.
 *
 *  Module for a clean handling of attibutes values
 *
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


typedef enum {INT, FLOAT, TVOID} type;

struct ATTRIBUTE {
  char * name;
  int int_val;
  float float_val;
  type type_val;
  int reg_number;
  
  /* other attribute's fields can goes here */ 

};

typedef struct ATTRIBUTE * attribute;




attribute new_attribute ();// returns the pointeur to a newly allocated (but uninitialized) attribute value structure */
int new_reg_num();// return the number of an unused register
int new_label();// return the value of an unused label (for loops and conditionals)

void print_func( attribute r); // print the function related the given attribute
void print_affect(attribute r, attribute s); // print the assignements
void print_affect_app(); // print the assignement of a function call to a variable
void print_affect_p(attribute r, attribute s, int reg_num); // print the pointer assignements



attribute plus_attribute(attribute x, attribute y);
attribute mult_attribute(attribute x, attribute y);
attribute minus_attribute(attribute x, attribute y);
attribute div_attribute(attribute x, attribute y);
attribute neg_attribute(attribute x);
attribute bool_attribute(attribute x, char* op, attribute y);


#endif

