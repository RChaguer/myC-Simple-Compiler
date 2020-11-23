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

#define CAPACITY 10

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




attribute new_attribute ();
/* returns the pointeur to a newly allocated (but uninitialized) attribute value structure */
int new_reg_num();
int new_label();
void write_type(attribute r);
//void write_stars(attribute r);
void write_func( attribute r);
void write_aff(attribute r, attribute s);
void write_aff_app();
void write_aff_p(attribute r, attribute s, int reg_num);


attribute plus_attribute(attribute x, attribute y);
attribute mult_attribute(attribute x, attribute y);
attribute minus_attribute(attribute x, attribute y);
attribute div_attribute(attribute x, attribute y);
attribute neg_attribute(attribute x);
attribute bool_attribute(attribute x, char* op, attribute y);


#endif

