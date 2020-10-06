%{
    #include "lex.yy.c"
    #include "node.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    const int NON_TER = 0xffff;
    void yyerror(const char* msg) {}
    NODE* root;
%}

%token<node> INT FLOAT CHAR 
%token<node> ID
%token<node> TYPE STRUCT
%token<node> IF ELSE WHILE RETURN
%token<node> DOT SEMI COMMA
%token<node> ASSIGN
%token<node> LT LE GT GE NE EQ
%token<node> PLUS MINUS MUL DIV
%token<node> AND OR NOT 
%token<node> LP RP LB RB LC RC

%token NID LEADING_ZERO NONHEX

%type<node> Program ExtDecList ExtDef ExtDefList
%type<node> Specifier StructSpecifier
%type<node> VarDec FunDec VarList ParamDec
%type<node> CompSt StmtList CloseStmt OpenStmt Stmt
%type<node> DecList Dec DefList Def Exp Args
%type<node> UnaryExp BinaryExp TrinaryExp

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
Program: ExtDefList {
        NODE* cur = new_node((NODE_VAL)"Program", NON_TER, $1->lineno);
        insert(cur, $1);
        root = cur;
    };

ExtDefList: ExtDef ExtDefList {
        NODE* cur = new_node((NODE_VAL)"ExtDefList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty {
        NODE* cur = new_node((NODE_VAL)"ExtDefList", NON_TER, yylineno);
        $$ = cur;
    };
    
ExtDef: Specifier ExtDecList SEMI {
        NODE* cur = new_node((NODE_VAL)"ExtDef", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
}
    | Specifier SEMI {
        NODE* cur = new_node((NODE_VAL)"ExtDef", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | Specifier FunDec CompSt {
        NODE* cur = new_node((NODE_VAL)"ExtDef", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
    
ExtDecList: VarDec {
        NODE* cur = new_node((NODE_VAL)"ExtDecList", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec COMMA ExtDecList {
        NODE* cur = new_node((NODE_VAL)"ExtDecList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };

/* Specifiers */
Specifier: TYPE {
        NODE* cur = new_node((NODE_VAL)"Specifier", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | StructSpecifier{
        NODE* cur = new_node((NODE_VAL)"Specifier", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };

StructSpecifier: STRUCT ID LC DefList RC {
        NODE* cur = new_node((NODE_VAL)"StructSpecifier", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | STRUCT ID {
        NODE* cur = new_node((NODE_VAL)"StructSpecifier", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    };

/* Declaration */
VarDec: ID {
        NODE* cur = new_node((NODE_VAL)"VarDec", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec LB INT RB {
        NODE* cur = new_node((NODE_VAL)"VarDec", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    };

FunDec: ID LP VarList RP {
        NODE* cur = new_node((NODE_VAL)"FunDec", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | ID LP RP {
        NODE* cur = new_node((NODE_VAL)"FunDec", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };

VarList: ParamDec COMMA VarList {
        NODE* cur = new_node((NODE_VAL)"VarList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | ParamDec {
        NODE* cur = new_node((NODE_VAL)"VarList", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };

ParamDec: Specifier VarDec {
        NODE* cur = new_node((NODE_VAL)"ParamDec", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
};

/* Statement */
CompSt: LC DefList StmtList RC {
        NODE* cur = new_node((NODE_VAL)"CompSt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
};
StmtList: Stmt StmtList {
        NODE* cur = new_node((NODE_VAL)"StmtList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty {
        NODE* cur = new_node((NODE_VAL)"StmtList", NON_TER, yylineno);
        $$ = cur;
    };

Stmt: OpenStmt
    | CloseStmt;
    
OpenStmt: IF LP Exp RP Stmt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
}
    | IF LP Exp RP CloseStmt ELSE OpenStmt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }
    | WHILE LP Exp RP OpenStmt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    };

CloseStmt: Exp SEMI {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | CompSt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | RETURN Exp SEMI {        
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | IF LP Exp RP CloseStmt ELSE CloseStmt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }
    | WHILE LP Exp RP CloseStmt {
        NODE* cur = new_node((NODE_VAL)"Stmt", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    };



/* Internal Definition */
DefList: Def DefList {
        NODE* cur = new_node((NODE_VAL)"DefList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty {
        NODE* cur = new_node((NODE_VAL)"DefList", NON_TER, yylineno);
    };
    
Def: Specifier DecList SEMI {
        NODE* cur = new_node((NODE_VAL)"Def", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
};
DecList: Dec {
        NODE* cur = new_node((NODE_VAL)"DecList", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
}
    | Dec COMMA DecList {
        NODE* cur = new_node((NODE_VAL)"DecList", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
Dec: VarDec {
        NODE* cur = new_node((NODE_VAL)"Dec", NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
}
    | VarDec ASSIGN Exp{
        NODE* cur = new_node((NODE_VAL)"Dec", NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };

/* Expression */
QuadExp: ID LP Args RP
    | Exp LB Exp RB;

TrinaryExp: Exp ASSIGN Exp
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
    | ID LP RP
    | Exp DOT ID
    | LP Exp RP;
BinaryExp: MINUS Exp %prec UMINUS
    | NOT Exp;

UnaryExp: ID
    | INT
    | FLOAT
    | CHAR;

Exp: UnaryExp {
    NODE* cur = new_node((NODE_VAL) "Exp", NON_TER, )
}
Args: Exp COMMA Args
    | Exp;
