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
%type <val> cond inst bool_cond else
%type <val> fun_head params arglist args app


%start prog  
 


%%

prog : func_list               {}
;

func_list : func_list fun      {}
| fun                          {}
;


// I. Functions

fun : type fun_head fun_body        {finish_func();}
;

fun_head : ID PO PF            { set_symbol_value($<val>1->name, $1, IS_FUNC);
                                 write_func($1);
                                }
| ID PO params PF              { 
                                $1->type_val = $<val>0->type_val;
                                set_symbol_value($1->name, $1,IS_FUNC);
                                write_func($1);
                                }
;

params: type ID vir params     {  
                                 $2->type_val = $1->type_val;
                                 set_symbol_value($2->name, $2,OTHER);
                                }
| type ID                      { 
                                 $2->type_val = $1->type_val;
                                 $2->reg_number = new_reg_num();
                                  set_symbol_value($2->name, $2,OTHER);
                                }

vlist: ID vir vlist              { $1->type_val = $<val>0->type_val;
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

fun_body : AO block AF         { printf("}\n\n");}
;

// Block
block:
decl_list inst_list            {}
;

// I. Declarations

decl_list : decl_list decl     {}
|                               %empty {}
;

decl: var_decl PV              {}
;

var_decl : type vlist          {  
                                    $2 -> type_val = $1->type_val;
                                }
;

type
: typename pointer             { $$ = $2;
                                 $$->type_val = $1->type_val;}
| typename                     { $$ = $1;}
;

typename
: TINT                          {$$ = new_attribute();
                                  $$->type_val = INT;}
| VOID                          {$$ = new_attribute();
                                  $$->type_val = TVOID;}
;

pointer
: pointer STAR                 { $$=$1;}
| STAR                         {$$ = new_attribute();}
;


// II. Intructions

inst_list: inst PV inst_list {}
| inst pvo                   {}
;

pvo : PV
| %empty 
;


inst:
exp                           {}
| AO block AF                 {}
| aff                         {}
| ret                         {}
| cond                        {}
| loop                        {}
| PV                          {}
| %empty                      {}
;


// II.1 Affectations

aff : ID EQ exp               { $1 = get_symbol_value($1->name);
                                write_aff($1, $3);}
| STAR exp  EQ exp            {}
;


// II.2 Return
ret : RETURN exp              {stack__return($2);}
| RETURN PO PF                {}
;

// II.3. Conditionelles
//           N.B. ces rêgles génèrent un conflit déclage reduction qui est résolu comme on le souhaite
//           i.e. en lisant un ELSE en entrée, si on peut faire une reduction elsop, on la fait...

cond :
if bool_cond inst elsop {printf("l%d:;\n", $3->int_val);}
;

elsop : else inst             {}
| %empty 
;

bool_cond : PO exp PF         { $$ = $2;
                                $$->int_val = new_label();
                                printf("if ( !ri%d ) goto l%d;\n",
                                $2->reg_number, $$->int_val);}
;

if : IF                       {}
;

else : ELSE                   { $$ = new_attribute();}
;

// II.4. Iterations

loop : while while_cond inst  {}
;

while_cond : PO exp PF        {}

while : WHILE                 {}
;


// II.3 Expressions
exp
// II.3.0 Exp. arithmetiques
: MOINS exp %prec UNA         {}
| exp PLUS exp                {$$ = plus_attribute($1,$3);}
| exp MOINS exp               {$$ = minus_attribute($1,$3);}
| exp STAR exp                {$$ = mult_attribute($1,$3);}
| exp DIV exp                 {$$ = mult_attribute($1,$3);}
| PO exp PF                   {$$ = $2;}
| ID                          {$$ = get_symbol_value($1->name);}
| app                         { 
                                $$->reg_number = get_next_register();
                                write_aff_app($$);
                                stack__push();
                                }
| NUMI                        {
                              $$->reg_number=get_next_register();
                              stack__push_numi($$);}

| NUMF                        {$$ = $1;
                                $$->reg_number = new_reg_num();
                                printf("float ri%d;\n", $$->reg_number);
                                printf("ri%d = %f;\n", $$->reg_number, $$->float_val);}

// II.3.1 Déréférencement

| STAR exp %prec UNA          {}

// II.3.2. Booléens

| NOT exp %prec UNA           {}
| exp INF exp                 { $$ = bool_attribute($1, "<", $3);}
| exp SUP exp                 { $$ = bool_attribute($1, ">", $3);}
| exp EQUAL exp               { $$ = bool_attribute($1, "==", $3);}
| exp DIFF exp                { $$ = bool_attribute($1, "!=", $3);}
| exp AND exp                 { $$ = bool_attribute($1, "&&", $3);}
| exp OR exp                  { $$ = bool_attribute($1, "||", $3);}

;

// II.4 Applications de fonctions

app : ID PO args PF            {stack__reset();}

args :  arglist               {printf("call_%s();\n",$<val>-1->name);}

|%empty                       { stack__save();
                                stack__new();
                                printf("call_%s();\n",$<val>-1->name);
                                
                                }
;

arglist : exp VIR arglist     {stack__push_param($1);
                              }
| exp                         { 
                                stack__save();
                                stack__new();
                                stack__push_param($1);                                
                              }
;



%% 
int main () {
 return yyparse ();
} 

