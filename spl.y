%{
    #include "lex.yy.c"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void yyerror(const char* msg) {}
%}

%token INT FLOAT CHAR 
%token ID
%token TYPE STRUCT
%token IF ELSE WHILE RETURN
%token DOT SEMI COMMA
%token ASSIGN
%token LT LE GT GE NE EQ
%token PLUS MINUS MUL DIV
%token AND OR NOT 
%token LP RP LB RB LC RC

%token NID LEADING_ZERO NONHEX

%right ASSIGN
%left OR
%left AND
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left MUL DIV
%right UMINUS NOT
%left LP RP LB RB DOT

%union {
    struct NODE* node;
}

%%

/* External Definition */
Program: ExtDefList;

ExtDefList: ExtDef ExtDefList
    | %empty;
    
ExtDef: Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt;
    
ExtDecList: VarDec
    | VarDec COMMA ExtDecList;

/* Specifiers */
Specifier: TYPE
    | StructSpecifier;

StructSpecifier: STRUCT ID LC DefList RC
    | STRUCT ID;

/* Declaration */
VarDec: ID
    | VarDec LB INT RB;

FunDec: ID LP VarList RP
    | ID LP RP;

VarList: ParamDec COMMA VarList
    | ParamDec;

ParamDec: Specifier VarDec;

/* Statement */
CompSt: LC DefList StmtList RC;
StmtList: Stmt StmtList
    | %empty;
    
Stmt: OpenStmt
    | CloseStmt;
    
OpenStmt: IF LP Exp RP Stmt
    | IF LP Exp RP CloseStmt ELSE OpenStmt
    | WHILE LP Exp RP OpenStmt;
    
CloseStmt: Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP CloseStmt ELSE CloseStmt
    | WHILE LP Exp RP CloseStmt;



/* Internal Definition */
DefList: Def DefList
    | %empty;
    
Def: Specifier DecList SEMI;
DecList: Dec
    | Dec COMMA DecList;
Dec: VarDec
    | VarDec ASSIGN Exp;

/* Expression */
Exp: Exp ASSIGN Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp LT Exp
    | Exp LE Exp
    | Exp GT Exp
    | Exp GE Exp
    | Exp NE Exp
    | Exp EQ Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp MUL Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp %prec UMINUS
    | NOT Exp
    | ID LP Args RP
    | ID LP RP
    | Exp LB Exp RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    | CHAR;
Args: Exp COMMA Args
    | Exp;
