/*
 *  Table des symboles.h
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 *  Associative array encoded as linked list of pair (symbol_name, symbol_value).
 *  To be used only with getter get_symbol_value and setter set_symbol_value.
 *
 *  Type attribute can be customized.
 *
 *  Symbol names must be valid sid from Table des chaines. 
 *
 */

#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

#include "Table_des_chaines.h"
#include "Attribute.h"

typedef enum {IS_FUNC,OTHER} boolean;

void start_block();
void finish_block();
void queue__init();


/* get the symbol value of symb_id from the symbol table, NULL if it fails */
attribute get_symbol_value(sid symb_id);

/* set the value of symbol symb_id to value, return NULL if it fails */
attribute set_symbol_value(sid symb_id, attribute value, boolean is_func);

/* reset the actual block or subblock temp declarative symbol table */
void reset_actual_symbol_table();

char* get_actual_function_end_label();

int get_next_register();
void finish_func();


#endif
