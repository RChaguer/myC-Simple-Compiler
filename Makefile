SHELL = /bin/bash
# Folders Path
SRC = src
BLD = build
TST = tst
TST_LIST = $(shell ls ${TST})
T_FLS = ${BLD}/H_C_Files
C_FLS = ${BLD}/Compiler_Files
BAR = %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

.SILENT: test %.myc lang lex.yy.c clean cleanCp
all	   : lang


build 			:   
				@if [ ! -d ${BLD} ]; then\
					mkdir ${BLD} ${T_FLS} ${C_FLS}; \
				fi

y.tab.h y.tab.c :	build ${SRC}/lang.y 
				@bison -v -y -d ${SRC}/lang.y -Wnone

lex.yy.c		:	${SRC}/lang.l y.tab.h
				@flex ${SRC}/lang.l 

lang			:	lex.yy.c y.tab.c ${SRC}/Table_des_symboles.c ${SRC}/Table_des_chaines.c ${SRC}/Attribute.c ${SRC}/stack.c
				@gcc -g -o lang lex.yy.c y.tab.c ${SRC}/Attribute.c ${SRC}/stack.c ${SRC}/Table_des_symboles.c ${SRC}/Table_des_chaines.c
				mv -t ${C_FLS} lex.yy.c y.tab.h y.tab.c lang y.output

%.myc			:	${TST}/$@
				@./compil.sh ${TST}/$@ 
				@echo -e "${BAR} Start of ${@:.myc=} Execution ${BAR}"
				@./${BLD}/${@:.myc=}
				@echo -e "${BAR}  End of ${@:.myc=} Execution  ${BAR}\n\n"

test			:	${TST_LIST}

cleanCp			:
				@rm -f  lex.yy.c *.o y.tab.h y.tab.c lang *~ y.output;
				
clean			:	cleanCp
				@if [ -d ${BLD} ]; then\
					rm -r ${BLD};\
				fi
				
