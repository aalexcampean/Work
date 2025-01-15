/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ARR = 258,
     VAR = 259,
     IF = 260,
     PRINT = 261,
     READINT = 262,
     READSTRING = 263,
     ELSE = 264,
     WHILE = 265,
     SETNTH = 266,
     GETNTH = 267,
     RETURN = 268,
     IDENTIFIER = 269,
     INTCONSTANT = 270,
     STRINGCONSTANT = 271,
     PLUS = 272,
     MINUS = 273,
     TIMES = 274,
     DIV = 275,
     MOD = 276,
     EQ = 277,
     BIGGER = 278,
     BIGGEREQ = 279,
     LESS = 280,
     LESSEQ = 281,
     EQQ = 282,
     NEQ = 283,
     AND = 284,
     OR = 285,
     SEMICOLON = 286,
     OPEN = 287,
     CLOSE = 288,
     BRACKETOPEN = 289,
     BRACKETCLOSE = 290,
     COMMA = 291
   };
#endif
/* Tokens.  */
#define ARR 258
#define VAR 259
#define IF 260
#define PRINT 261
#define READINT 262
#define READSTRING 263
#define ELSE 264
#define WHILE 265
#define SETNTH 266
#define GETNTH 267
#define RETURN 268
#define IDENTIFIER 269
#define INTCONSTANT 270
#define STRINGCONSTANT 271
#define PLUS 272
#define MINUS 273
#define TIMES 274
#define DIV 275
#define MOD 276
#define EQ 277
#define BIGGER 278
#define BIGGEREQ 279
#define LESS 280
#define LESSEQ 281
#define EQQ 282
#define NEQ 283
#define AND 284
#define OR 285
#define SEMICOLON 286
#define OPEN 287
#define CLOSE 288
#define BRACKETOPEN 289
#define BRACKETCLOSE 290
#define COMMA 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

