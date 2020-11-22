/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMI = 258,
    NUMF = 259,
    TINT = 260,
    ID = 261,
    AO = 262,
    AF = 263,
    PO = 264,
    PF = 265,
    PV = 266,
    VIR = 267,
    RETURN = 268,
    VOID = 269,
    EQ = 270,
    IF = 271,
    ELSE = 272,
    WHILE = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    DIFF = 277,
    EQUAL = 278,
    SUP = 279,
    INF = 280,
    PLUS = 281,
    MOINS = 282,
    STAR = 283,
    DIV = 284,
    DOT = 285,
    ARR = 286,
    UNA = 287
  };
#endif
/* Tokens.  */
#define NUMI 258
#define NUMF 259
#define TINT 260
#define ID 261
#define AO 262
#define AF 263
#define PO 264
#define PF 265
#define PV 266
#define VIR 267
#define RETURN 268
#define VOID 269
#define EQ 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define AND 274
#define OR 275
#define NOT 276
#define DIFF 277
#define EQUAL 278
#define SUP 279
#define INF 280
#define PLUS 281
#define MOINS 282
#define STAR 283
#define DIV 284
#define DOT 285
#define ARR 286
#define UNA 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "lang.y"
 
	struct ATTRIBUTE * val;

#line 125 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
