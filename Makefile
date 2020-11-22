all		:	lang

y.tab.h y.tab.c :	lang.y
			bison -v -y -d  lang.y
lex.yy.c	:	lang.l y.tab.h
			flex lang.l 
lang		:	lex.yy.c y.tab.c Table_des_symboles.c Table_des_chaines.c Attribute.c stack.c
			gcc -g -o lang lex.yy.c y.tab.c Attribute.c stack.c Table_des_symboles.c Table_des_chaines.c
clean		:	
			rm -f 	lex.yy.c *.o y.tab.h y.tab.c lang *~ y.output
