%{

#include "Table_des_symboles.h"
#include "Attribute.h"
#include "stack.h"

#include <stdio.h>
  
extern int yylex();
extern int yyparse();

void yyerror (char* s) {
  printf ("%s\n",s);
  }
		

%}

%union { 
	struct ATTRIBUTE * val;
}
%token <val> NUMI NUMF
%token TINT  // TFLOAT STRUCT
%token <val> ID
%token AO AF PO PF PV VIR
%token RETURN VOID EQ
%token <val> IF ELSE WHILE

%token <val> AND OR NOT DIFF EQUAL SUP INF
%token PLUS MOINS STAR DIV
%token DOT ARR

%left DIFF EQUAL SUP INF       // low priority on comparison
%left PLUS MOINS               // higher priority on + - 
%left STAR DIV                 // higher priority on * /
%left OR                       // higher priority on ||
%left AND                      // higher priority on &&
%left DOT ARR                  // higher priority on . and -> 
%nonassoc UNA                  // highest priority on unary operator
%nonassoc ELSE

%type <val> exp type pointer vir vlist typename  var_decl decl_list
%type <val> cond inst bool_cond else if while while_cond
%type <val> fun_head params arglist args app


%start prog  
 


%%

prog : head func_list               {}
;

head : %empty                 { stack__init();
                                queue__init();
                              }
;

func_list : func_list fun      {}
| fun                          {}
;


// I. Functions

fun : type fun_head fun_body        { finish_func();}
;

fun_head : ID PO PF             { set_symbol_value($<val>1->name, $1, IS_FUNC);
                                  print_func($1);
                                }
| ID PO params PF               { $1->type_val = $<val>0->type_val;
                                  set_symbol_value($1->name, $1,IS_FUNC);
                                  print_func($1);
                                }
;

params: type ID vir params      { $2->type_val = $1->type_val;
                                  set_symbol_value($2->name, $2,OTHER);
                                }
| type ID                       { $2->type_val = $1->type_val;
                                  $2->reg_number = new_reg_num();
                                  set_symbol_value($2->name, $2,OTHER);
                                }

vlist: ID vir vlist             { $1->type_val = $<val>0->type_val;
                                  set_symbol_value($1->name, $1,OTHER);
                                  stack__push();
                                }
| ID                            { $1->type_val = $<val>0->type_val;
                                  set_symbol_value($1->name, $1,OTHER);
                                  stack__push();
                                }
;

vir : VIR                      {}
;

fun_body : func_AO block func_AF    {}
;

func_AO : AO                        { printf("{\n");}
;

func_AF : AF                        { printf("%s:;\n", get_actual_function_end_label());
                                      printf("}\n");
                                    }
;

// Block

block:
decl_list inst_list            {}
;

// I. Declarations

decl_list : decl_list decl     { reset_actual_symbol_table();}
|%empty                        { reset_actual_symbol_table();}
;

decl: var_decl PV              {}
;

var_decl : type vlist          { $2 -> type_val = $1->type_val;}
;

type
: typename pointer             { $$ = $2;
                                 $$->type_val = $1->type_val;
                               }
| typename                     { $$ = $1;}
;

typename
: TINT                          { $$ = new_attribute();
                                  $$->type_val = INT;
                                } 
| VOID                          { $$ = new_attribute();
                                  $$->type_val = TVOID;
                                }
;

pointer
: pointer STAR                 { $$=$1;
                                 $$->stars_number++;
                               }
| STAR                         { $$ = new_attribute();
                                 $$->stars_number++;
                               }
;


// II. Intructions-

inst_list: inst PV inst_list {}
| inst pvo                   {}
| cond inst_list             {}
| loop inst_list             {}
;

pvo : PV
| %empty 
;

start_block: AO               { start_block();};
end_block: AF                 { finish_block();};

inst:
exp                           {}
| start_block block end_block {}
| aff                         {}
| ret                         {}
| PV                          {}
| %empty                      {}
;


// II.1 Affectations

aff : ID EQ exp               { $1 = get_symbol_value($1->name);
                                print_affect($1, $3);
                              }
| STAR exp  EQ exp            { print_affect_p($2, $4);}
;


// II.2 Return
ret : RETURN exp              { stack__return($2);
                                printf("goto %s;\n", get_actual_function_end_label());
                              }
| RETURN PV                   { printf("goto %s;\n", get_actual_function_end_label());}
;

// II.3. Conditionelles
//           N.B. ces rêgles génèrent un conflit déclage reduction qui est résolu comme on le souhaite
//           i.e. en lisant un ELSE en entrée, si on peut faire une reduction elsop, on la fait...

cond :
if bool_cond inst_list elsop {}
;

elsop : else inst_list            { printf("l%d:;\n", $1->label_number);}
| %empty                          { printf("l%d:;\n", $<val>-1->label_number);}
;

bool_cond : PO exp PF         { $$=new_attribute();
                                $$->label_number = new_label();
                                printf("if ( !*(fp + %d) ) goto l%d;\n",
                                $2->reg_number, $$->label_number);
                              }
                                
;

if : IF                       {}
;

else : ELSE                   { $$ = new_attribute();
                                $$->label_number = new_label();
                                printf("goto l%d;\nl%d:;\n", $$->label_number, $<val>-1->label_number);
                              }
;

// II.4. Iterations

loop : while while_cond inst_list  { printf("goto l%d;\nl%d:;\n",$1->reg_number,$2->reg_number);}
;

while_cond : PO exp PF        { $$=new_attribute();
                                $$->label_number = new_label();
                                printf("if ( !*(fp + %d) ) goto l%d;\n",
                                $2->reg_number, $$->label_number);
                              }

while : WHILE                 { $$ = new_attribute();
                                $$->reg_number = new_label();
                                printf("l%d:;\n", $$->label_number);
                              }
;


// II.3 Expressions
exp
// II.3.0 Exp. arithmetiques
: MOINS exp %prec UNA         { $$ = neg_attribute($2);}
| exp PLUS exp                { $$ = plus_attribute($1,$3);}
| exp MOINS exp               { $$ = minus_attribute($1,$3);}
| exp STAR exp                { $$ = mult_attribute($1,$3);}
| exp DIV exp                 { $$ = div_attribute($1,$3);}
| PO exp PF                   { $$ = $2;}
| ID                          { $$ = get_symbol_value($1->name);}
| app                         { $$->reg_number = get_next_register();
                                print_affect_app($$);
                                stack__push();
                              }
| NUMI                        { $$->reg_number=get_next_register();
                                stack__push_numi($$);
                              }
| NUMF                        {}

// II.3.1 Déréférencement

| STAR exp %prec UNA          { $$ = new_attribute();
                                $$->reg_number = new_reg_num();
                                stack__push_dereference($2);
                              }

// II.3.2. Booléens

| NOT exp %prec UNA           { $$ = not_attribute($2);}
| exp INF exp                 { $$ = bool_attribute($1, "<", $3);}
| exp SUP exp                 { $$ = bool_attribute($1, ">", $3);}
| exp EQUAL exp               { $$ = bool_attribute($1, "==", $3);}
| exp DIFF exp                { $$ = bool_attribute($1, "!=", $3);}
| exp AND exp                 { $$ = bool_attribute($1, "&&", $3);}
| exp OR exp                  { $$ = bool_attribute($1, "||", $3);}

;

// II.4 Applications de fonctions

app : ID PO args PF           { stack__reset();}

args :  arglist               { printf("call_%s();\n",$<val>-1->name);}

|%empty                       { stack__save();
                                stack__new();
                                printf("call_%s();\n",$<val>-1->name);
                              }
;

arglist : exp VIR arglist     { stack__push_param($1);}
| exp                         { stack__save();
                                stack__new();
                                stack__push_param($1);                                
                              }
;



%% 
int main () {
 return yyparse ();
} 

