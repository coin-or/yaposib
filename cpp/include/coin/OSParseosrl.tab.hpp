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
     ATTRIBUTETEXT = 258,
     ELEMENTTEXT = 259,
     ITEMTEXT = 260,
     INTEGER = 261,
     DOUBLE = 262,
     QUOTE = 263,
     TWOQUOTES = 264,
     GREATERTHAN = 265,
     ENDOFELEMENT = 266,
     OSRLSTART = 267,
     OSRLSTARTEMPTY = 268,
     OSRLATTRIBUTETEXT = 269,
     OSRLEND = 270,
     GENERALSTART = 271,
     GENERALEND = 272,
     SYSTEMSTART = 273,
     SYSTEMEND = 274,
     SERVICESTART = 275,
     SERVICEEND = 276,
     JOBSTART = 277,
     JOBEND = 278,
     SERVICEURISTARTANDEND = 279,
     SERVICEURISTART = 280,
     SERVICEURIEND = 281,
     SERVICENAMESTARTANDEND = 282,
     SERVICENAMESTART = 283,
     SERVICENAMEEND = 284,
     INSTANCENAMESTARTANDEND = 285,
     INSTANCENAMESTART = 286,
     INSTANCENAMEEND = 287,
     JOBIDSTARTANDEND = 288,
     JOBIDSTART = 289,
     JOBIDEND = 290,
     TIMINGINFORMATIONSTART = 291,
     TIMINGINFORMATIONEND = 292,
     TIMESTARTANDEND = 293,
     TIMESTART = 294,
     TIMEEND = 295,
     OPTIMIZATIONSTART = 296,
     OPTIMIZATIONEND = 297,
     SOLUTIONSTART = 298,
     SOLUTIONEND = 299,
     VALUESSTART = 300,
     VALUESEND = 301,
     DUALVALUESSTART = 302,
     DUALVALUESEND = 303,
     VARIABLESSTART = 304,
     VARIABLESEND = 305,
     VARSTART = 306,
     VAREND = 307,
     OBJECTIVESSTART = 308,
     OBJECTIVESEND = 309,
     OBJSTART = 310,
     OBJEND = 311,
     CONSTRAINTSSTART = 312,
     CONSTRAINTSEND = 313,
     CONSTART = 314,
     CONEND = 315,
     STATUSSTART = 316,
     STATUSEND = 317,
     GENERALSTATUSSTART = 318,
     GENERALSTATUSEND = 319,
     MESSAGESTART = 320,
     MESSAGEEND = 321,
     MESSAGESTARTANDEND = 322,
     OTHERSTART = 323,
     OTHEREND = 324,
     NUMBEROFTIMESATT = 325,
     NUMBEROFSOLUTIONSATT = 326,
     NUMBEROFVARIABLESATT = 327,
     NUMBEROFCONSTRAINTSATT = 328,
     NUMBEROFOBJECTIVESATT = 329,
     NUMBEROFOTHERVARIABLERESULTSATT = 330,
     NUMBEROFOTHEROBJECTIVERESULTSATT = 331,
     NUMBEROFOTHERCONSTRAINTRESULTSATT = 332,
     NUMBEROFOTHERSOLUTIONRESULTSATT = 333,
     NUMBEROFITEMSATT = 334,
     OTHERSOLUTIONRESULTSSTART = 335,
     OTHERSOLUTIONRESULTSEND = 336,
     OTHERSOLUTIONRESULTSTART = 337,
     OTHERSOLUTIONRESULTEND = 338,
     ITEMSTART = 339,
     ITEMEND = 340,
     ITEMSTARTANDEND = 341,
     ITEMEMPTY = 342,
     NUMBEROFVARATT = 343,
     NUMBEROFOBJATT = 344,
     NUMBEROFCONATT = 345,
     TARGETOBJECTIVEIDXATT = 346,
     IDXATT = 347,
     TYPEATT = 348,
     EMPTYTYPEATT = 349,
     DESCRIPTIONATT = 350,
     EMPTYDESCRIPTIONATT = 351,
     NAMEATT = 352,
     EMPTYNAMEATT = 353,
     CATEGORYATT = 354,
     EMPTYCATEGORYATT = 355,
     UNITATT = 356,
     EMPTYUNITATT = 357,
     VALUEATT = 358,
     EMPTYVALUEATT = 359,
     DUMMY = 360
   };
#endif
/* Tokens.  */
#define ATTRIBUTETEXT 258
#define ELEMENTTEXT 259
#define ITEMTEXT 260
#define INTEGER 261
#define DOUBLE 262
#define QUOTE 263
#define TWOQUOTES 264
#define GREATERTHAN 265
#define ENDOFELEMENT 266
#define OSRLSTART 267
#define OSRLSTARTEMPTY 268
#define OSRLATTRIBUTETEXT 269
#define OSRLEND 270
#define GENERALSTART 271
#define GENERALEND 272
#define SYSTEMSTART 273
#define SYSTEMEND 274
#define SERVICESTART 275
#define SERVICEEND 276
#define JOBSTART 277
#define JOBEND 278
#define SERVICEURISTARTANDEND 279
#define SERVICEURISTART 280
#define SERVICEURIEND 281
#define SERVICENAMESTARTANDEND 282
#define SERVICENAMESTART 283
#define SERVICENAMEEND 284
#define INSTANCENAMESTARTANDEND 285
#define INSTANCENAMESTART 286
#define INSTANCENAMEEND 287
#define JOBIDSTARTANDEND 288
#define JOBIDSTART 289
#define JOBIDEND 290
#define TIMINGINFORMATIONSTART 291
#define TIMINGINFORMATIONEND 292
#define TIMESTARTANDEND 293
#define TIMESTART 294
#define TIMEEND 295
#define OPTIMIZATIONSTART 296
#define OPTIMIZATIONEND 297
#define SOLUTIONSTART 298
#define SOLUTIONEND 299
#define VALUESSTART 300
#define VALUESEND 301
#define DUALVALUESSTART 302
#define DUALVALUESEND 303
#define VARIABLESSTART 304
#define VARIABLESEND 305
#define VARSTART 306
#define VAREND 307
#define OBJECTIVESSTART 308
#define OBJECTIVESEND 309
#define OBJSTART 310
#define OBJEND 311
#define CONSTRAINTSSTART 312
#define CONSTRAINTSEND 313
#define CONSTART 314
#define CONEND 315
#define STATUSSTART 316
#define STATUSEND 317
#define GENERALSTATUSSTART 318
#define GENERALSTATUSEND 319
#define MESSAGESTART 320
#define MESSAGEEND 321
#define MESSAGESTARTANDEND 322
#define OTHERSTART 323
#define OTHEREND 324
#define NUMBEROFTIMESATT 325
#define NUMBEROFSOLUTIONSATT 326
#define NUMBEROFVARIABLESATT 327
#define NUMBEROFCONSTRAINTSATT 328
#define NUMBEROFOBJECTIVESATT 329
#define NUMBEROFOTHERVARIABLERESULTSATT 330
#define NUMBEROFOTHEROBJECTIVERESULTSATT 331
#define NUMBEROFOTHERCONSTRAINTRESULTSATT 332
#define NUMBEROFOTHERSOLUTIONRESULTSATT 333
#define NUMBEROFITEMSATT 334
#define OTHERSOLUTIONRESULTSSTART 335
#define OTHERSOLUTIONRESULTSEND 336
#define OTHERSOLUTIONRESULTSTART 337
#define OTHERSOLUTIONRESULTEND 338
#define ITEMSTART 339
#define ITEMEND 340
#define ITEMSTARTANDEND 341
#define ITEMEMPTY 342
#define NUMBEROFVARATT 343
#define NUMBEROFOBJATT 344
#define NUMBEROFCONATT 345
#define TARGETOBJECTIVEIDXATT 346
#define IDXATT 347
#define TYPEATT 348
#define EMPTYTYPEATT 349
#define DESCRIPTIONATT 350
#define EMPTYDESCRIPTIONATT 351
#define NAMEATT 352
#define EMPTYNAMEATT 353
#define CATEGORYATT 354
#define EMPTYCATEGORYATT 355
#define UNITATT 356
#define EMPTYUNITATT 357
#define VALUEATT 358
#define EMPTYVALUEATT 359
#define DUMMY 360




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE

{
	double dval;
	int ival;
	char* sval;
}
/* Line 1489 of yacc.c.  */

	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


