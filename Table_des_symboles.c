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
#include <stdio.h>

/* The storage structure is implemented as a linked chain */

/* linked element def */

typedef struct elem {
	sid symbol_name;
	attribute symbol_value;
	struct elem * next;
} elem;

/* linked chain initial element */
static elem * storage=NULL;
static int register_number = 1;


/* get the symbol value of symb_id from the symbol table */
attribute get_symbol_value(sid symb_id) {
	elem * tracker=storage;

	/* look into the linked list for the symbol value */
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return tracker -> symbol_value; 
		tracker = tracker -> next;
	}
    
	/* if not found does cause an error */
	fprintf(stderr,"Error : symbol %s is not a valid defined symbol\n",(char *) symb_id);
	exit(-1);
};

int get_next_register(){
	return register_number++;
}


/* set the value of symbol symb_id to value */
attribute set_symbol_value(sid symb_id,attribute value,boolean b) {

	elem * tracker;
	
	/* look for the presence of symb_id in storage */

	tracker = storage;
	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			tracker -> symbol_value = value;
			return tracker -> symbol_value;
		}
		tracker = tracker -> next;
	}
	
	/* otherwise insert it at head of storage with proper value */
	
	tracker = malloc(sizeof(elem));

	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;
	tracker -> next = storage;
	if(b == OTHER){
		tracker->symbol_value->reg_number = register_number;
		register_number ++;
	}
	storage = tracker;
	return storage -> symbol_value;
}



/*void declar_params(int nb_params){
	elem *tracker;
	tracker = storage;
	while (nb_params--)
	{
		write_type(tracker->symbol_value);
		printf(" ri%d = %s;\n", tracker->symbol_value->reg_number, tracker->symbol_name);
		tracker = tracker->next;
	}
}
*/

void finish_func()
{
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
}