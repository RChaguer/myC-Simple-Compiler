/*
 *  Table des symboles.c
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 */

#include "Table_des_symboles.h"
#include "Attribute.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define CAPACITY 10


/* The storage structure is implemented as a linked chain */

/* linked element def */
typedef struct elem {
	sid symbol_name;
	attribute symbol_value;
	struct elem * next;
} elem;

/* SubBlock queue */
typedef struct queue {
  elem **tab;
  int head;
  int capacity;
} queue;


/* Global variables used */
static elem * func_storage = NULL;
static elem * storage=NULL;
static elem * actual_block_storage = NULL;
static int register_number = 1;
char* actual_function_end_label = "end_label";
static queue q;


/* Register Number management function */
int get_next_register() {
	return register_number++;
}


/* Queue utility methods */
void queue__initialize(queue *s) {
  s->head = 0;
  s->capacity = CAPACITY;
  s->tab = malloc(sizeof(elem*) * CAPACITY);
  assert(s->tab != NULL);
}

void queue__push(elem* x, queue *s) {
  if (s->head < s->capacity)
  {
    s->head++;
    s->tab[s->head] = x;
  }
  else
  {
    s->tab = realloc(s->tab, sizeof(elem*) * CAPACITY * 2);
    assert(s->tab != NULL);
    s->capacity *= 2;
    s->head++;
    s->tab[s->head] = x;
  }
}

elem* queue__pop(queue *s) {
  elem* x = s->tab[s->head];
  s->head--;
  return x;
}

int queue__is_empty(queue *s) {
  if (s->head == 0)
    return 1;
  return 0;
}

void queue__init() {
	queue__initialize(&q);
}


/* Block management functions */
void start_block() {
	queue__push(storage,&q);
}

void finish_block() {
	elem * tracker = storage;
	if(!queue__is_empty(&q)){
		storage = queue__pop(&q);
	}
	elem *to_free;
	while (tracker!=storage)
	{
		to_free = tracker;
		tracker = tracker->next;
		free(to_free);
	}
}


/* Symbol table management functions */
/* get the symbol value of symb_id from the symbol table */
attribute get_symbol_value(sid symb_id, boolean type) {
	elem * tracker;

	if (type == IS_FUNC){
		tracker=func_storage;}
	else {
		tracker=storage;}

	/* look into the linked list for the symbol value */
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return tracker -> symbol_value; 
		tracker = tracker -> next;
	}
    
	/* if not found does cause an error */
	fprintf(stderr,"Error : symbol %s is not a valid defined symbol\n",(char *) symb_id);
	exit(-1);
};

/* set the value of symbol symb_id to value */
attribute set_symbol_value(sid symb_id,attribute value,boolean type) {

	elem * tracker;	
	elem *actual_tracker;

	if (type == IS_FUNC)
		tracker = func_storage;
	else
		tracker = actual_block_storage;
	
	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			fprintf(stderr,"Error : symbol %s is already defined in the same actual subBlock or a function name, choose another valid symbol\n",(char *) symb_id);
			exit(-1);
		}
		tracker = tracker -> next;
	}

	tracker = malloc(sizeof(elem));

	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;

	if (type == IS_FUNC) {
		tracker -> next = func_storage;
		func_storage = tracker;
		return func_storage -> symbol_value;
	} else {
		tracker -> next = storage;
		storage = tracker;

		actual_tracker = malloc(sizeof(elem));
		actual_tracker -> symbol_name = symb_id;
		actual_tracker -> symbol_value = value;
		actual_tracker -> next = actual_block_storage;
		actual_block_storage = actual_tracker;
	}
	if (type == OTHER) {
		tracker->symbol_value->reg_number = register_number;
		actual_tracker->symbol_value->reg_number = register_number;
		register_number ++;
	}
	return storage -> symbol_value;
}

char* get_actual_function_end_label() {
	return actual_function_end_label;
}

void finish_func() {
	elem *tracker;
	elem *to_free;
	tracker = storage;
	while (tracker)
	{
		to_free = tracker;
		tracker = tracker->next;
		free(to_free);
	}
	storage = NULL;
	register_number = 1;
	actual_block_storage = NULL;
}