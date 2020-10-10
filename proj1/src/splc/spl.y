%{
    #include "lex.yy.c"
    #include "../ext/node.h"
    #include "../ext/ce.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void yyerror(const char* msg) {  }
    NODE* root;
    extern int err_cnt;
    extern ERROR err_arr[MAX_ERR];
%}

%union {
    struct NODE* node;
}
%token<node> ERR
%token<node> INT FLOAT CHAR
%token<node> ID
%token<node> TYPE STRUCT
%token<node> IF ELSE WHILE FOR RETURN
%token<node> DOT SEMI COMMA
%token<node> ASSIGN
%token<node> LT LE GT GE NE EQ
%token<node> PLUS MINUS MUL DIV
%token<node> AND OR NOT 
%token<node> LP RP LB RB LC RC
%token<node> BinaryOp_1 BinaryOp_2 BinaryOp_3
%token NON_TER EMPTY
%type<node> ExpSuffix
%type<node> Program ExtDecList ExtDef ExtDefList
%type<node> Specifier StructSpecifier
%type<node> VarDec FunDec VarList ParamDec
%type<node> CompSt StmtList CloseStmt OpenStmt Stmt
%type<node> DecList Dec DefList Def Exp Args

%nonassoc ERR
%right ASSIGN
%left OR
%left AND
%left BinaryOp_1
%left BinaryOp_2
%left BinaryOp_3
%right UMINUS NOT
%left LP RP LB RB DOT



%%

/* External Definition */
Program: ExtDefList {
        NODE* cur = new_node("Program", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        root = cur;
    };

ExtDefList: ExtDef ExtDefList {
        NODE* cur = new_node("ExtDefList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty {
        $$ = NULL;
    };
    
ExtDef: Specifier ExtDecList SEMI {
        NODE* cur = new_node("ExtDef", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Specifier ExtDecList error SEMI {
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");
    }
    | Specifier SEMI {
        NODE* cur = new_node("ExtDef", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | error SEMI {
        add_err(SYNTAX, $2->lineno, "Missing Specifier", "");
    }
    | Specifier FunDec CompSt {
        NODE* cur = new_node("ExtDef", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
    | error FunDec CompSt {
        add_err(SYNTAX, $2->lineno, "Missing Specifier", "");
    }
    
ExtDecList: VarDec {
        NODE* cur = new_node("ExtDecList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec COMMA ExtDecList {
        NODE* cur = new_node("ExtDecList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };

/* Specifiers */
Specifier: TYPE {
        NODE* cur = new_node("Specifier", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | StructSpecifier{
        NODE* cur = new_node("Specifier", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };

StructSpecifier: STRUCT ID LC DefList RC {
        NODE* cur = new_node("StructSpecifier", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | STRUCT ID {
        NODE* cur = new_node("StructSpecifier", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    };

/* Declaration */
VarDec: ID {
        NODE* cur = new_node("VarDec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec LB INT RB {
        NODE* cur = new_node("VarDec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    };

FunDec: ID LP VarList RP {
        NODE* cur = new_node("FunDec", 0, NON_TER, $1->lineno);
        fflush(stdout);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | ID LP RP {
        NODE* cur = new_node("FunDec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
    | ID LP VarList error LC {
        unput('{');
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | ID LP error LC {
        unput('{');
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    };

VarList: ParamDec COMMA VarList {
        NODE* cur = new_node("VarList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | ParamDec {
        NODE* cur = new_node("VarList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };

ParamDec: Specifier VarDec {
        NODE* cur = new_node("ParamDec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
}
    | error VarDec {
        add_err(SYNTAX, $2->lineno, "Missing Semicolon", "");
};

/* Statement */
CompSt: LC DefList StmtList RC {
        NODE* cur = new_node("CompSt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
};
StmtList: Stmt StmtList {
        NODE* cur = new_node("StmtList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty { 
        $$ = NULL;
    };

Stmt: OpenStmt
    | CloseStmt;
    
OpenStmt: IF LP Exp RP Stmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | IF LP Exp error Stmt {
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | IF LP Exp RP CloseStmt ELSE OpenStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }
    | IF LP Exp error CloseStmt ELSE OpenStmt {
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | FOR LP Exp SEMI Exp SEMI Exp RP OpenStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        insert(cur, $8);
        insert(cur, $9);
    }
    | WHILE LP Exp RP OpenStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | WHILE LP Exp error OpenStmt {
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
;

CloseStmt: SEMI {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | Exp SEMI {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | Exp error SEMI {
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");
    }
    | CompSt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | RETURN Exp SEMI {        
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | RETURN Exp error SEMI {     
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");   
    }
    | IF LP Exp RP CloseStmt ELSE CloseStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }
    | IF LP Exp error CloseStmt ELSE CloseStmt {
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");   
    }
    | FOR LP Exp SEMI Exp SEMI Exp RP CloseStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        insert(cur, $8);
        insert(cur, $9);
    }
    | WHILE LP Exp RP CloseStmt {
        NODE* cur = new_node("Stmt", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | WHILE LP Exp error CloseStmt {
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");   
    };



/* Internal Definition */
DefList: Def DefList {
        NODE* cur = new_node("DefList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty { 
        $$ = NULL;
    };
    
Def: Specifier DecList SEMI {
        NODE* cur = new_node("Def", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | error DecList SEMI {
        add_err(SYNTAX, yylineno, "Missing Specifier", "");
    }
    | Specifier DecList error SEMI {
        add_err(SYNTAX, $1->lineno, "Missing Semicolon", "");
    };
DecList: Dec {
        NODE* cur = new_node("DecList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | Dec COMMA DecList {
        NODE* cur = new_node("DecList", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
Dec: VarDec {
        NODE* cur = new_node("Dec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
}
    | VarDec ASSIGN Exp{
        NODE* cur = new_node("Dec", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };

/* Expression */
ExpSuffix: DOT
    | COMMA
    | LP
    | LB
    | BinaryOp_1
    | BinaryOp_2
    | BinaryOp_3
    | AND
    | OR
    | ASSIGN;
    | SEMI;
    Exp: Exp BinaryOp_1 Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp BinaryOp_2 Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp BinaryOp_3 Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp ASSIGN Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp AND Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp OR Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp ERR Exp {
        
    }
    | MINUS Exp %prec UMINUS {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | NOT Exp {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | ID LP Args RP {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | Exp LB Exp RB {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | ID LP RP {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp DOT ID {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | LP Exp RP {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | ID {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | FLOAT{
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | CHAR {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };
    | INT {
        NODE* cur = new_node("Exp", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | ERR {

    }
    | ID LP Args error ExpSuffix {
        unput(*$5->node_val);
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | ID LP error ExpSuffix {
        unput(*$4->node_val);
        add_err(SYNTAX, $1->lineno, "Missing Right Parenthesis.", "");
    };
Args: Exp COMMA Args{
        NODE* cur = new_node("Args", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp {
        NODE* cur = new_node("Args", 0, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };
%%

int main(int argc,char *argv[])
{    
    FILE *fin=NULL;
    extern FILE* yyin;
    /* extern int yydebug;
    yydebug = 1; */
    fin=fopen(argv[1],"r"); 
    if(fin==NULL)
    {
        printf("cannot open reading file.\n");
        return -1;
    }
    yyin=fin;
    yyparse();
    if(!is_err())
        print_tree(root, 0);
    else for(int i = 0; i < err_cnt; i++)
        print_err(err_arr+i);
    fclose(fin);
    return 0;
}