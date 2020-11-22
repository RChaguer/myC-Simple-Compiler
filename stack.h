#ifndef STACK_H
#define STACK_H

#include "Attribute.h"

void stack__init();
void stack__save();
void stack__new();
void stack__push();
void stack__reset();
void stack__return(attribute x);
void stack__push_param(attribute x);
void stack__push_numi(attribute x);
#endif