%{
    #include "lex.yy.c"
    #include "../ext/node.h"
    #include "../ext/ce.h"
    #include "../../spp/spp.h"
    #include "../../ssa/ssa.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fstream>
    void yyerror(const char* msg) { printf("FUCK"); }
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
%token NON_TER EMPTY END

%type<node> NullableExp
%type<node> ExpSuffix
%type<node> Program ExtDecList ExtDef ExtDefList
%type<node> Specifier StructSpecifier
%type<node> VarDec FunDec VarList ParamDec
%type<node> CompSt StmtList CloseStmt OpenStmt Stmt
%type<node> DecList Dec DefList Def Exp Args
%type<node> EID
%nonassoc ERR
%right ASSIGN
%left OR
%left AND
%left BinaryOp_1
%left BinaryOp_2 MINUS
%left BinaryOp_3
%right UMINUS NOT
%left LP RP LB RB DOT
%%

/* External Definition */
Program: ExtDefList {
        NODE* cur = new_node("Program", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        set_root(cur);
    };

ExtDefList: ExtDef ExtDefList {
        NODE* cur = new_node("ExtDefList", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty {
        $$ = NULL;
    };
    
ExtDef: Specifier ExtDecList SEMI {
        NODE* cur = new_node("ExtDef", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Specifier SEMI {
        NODE* cur = new_node("ExtDef", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }

    | Specifier FunDec CompSt {
        NODE* cur = new_node("ExtDef", 3, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Specifier ExtDecList error SEMI {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
    }
    | Specifier ExtDecList error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
        
    }
    | error SEMI {
        add_err(ErrorType::SYNTAX, $2->lineno, "Missing Specifier", "");
    }
    | error FunDec CompSt {
        add_err(ErrorType::SYNTAX, $2->lineno, "Missing Specifier", "");
    };
    
ExtDecList: VarDec {
        NODE* cur = new_node("ExtDecList", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec COMMA ExtDecList {
        NODE* cur = new_node("ExtDecList", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }

/* Specifiers */
Specifier: TYPE {
        NODE* cur = new_node("Specifier", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | StructSpecifier {
        NODE* cur = new_node("Specifier", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    };

StructSpecifier: STRUCT EID LC DefList RC {
        NODE* cur = new_node("StructSpecifier", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | STRUCT EID {
        NODE* cur = new_node("StructSpecifier", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    };

/* Declaration */
VarDec: EID {
        NODE* cur = new_node("VarDec", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | VarDec LB INT RB {
        NODE* cur = new_node("VarDec", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    };

FunDec: EID LP VarList RP {
        NODE* cur = new_node("FunDec", 1, NON_TER, $1->lineno);
        fflush(stdout);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | EID LP RP {
        NODE* cur = new_node("FunDec", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | EID LP VarList error LC {
        unput('{');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | EID LP VarList error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
        
    }
    | EID LP error LC {
        unput('{');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | EID LP error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
        
    };

VarList: ParamDec {
        NODE* cur = new_node("VarList", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | ParamDec COMMA VarList {
        NODE* cur = new_node("VarList", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }

    | ParamDec COMMA error RP {
        unput(')');
        add_err(ErrorType::SYNTAX, $1->lineno, "Extra Comma", "");
    }

ParamDec: Specifier VarDec {
        NODE* cur = new_node("ParamDec", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
}
    | error VarDec {
        add_err(ErrorType::SYNTAX, $2->lineno, "Missing Specifier", "");
};

/* Statement */
CompSt: LC DefList StmtList RC {
        NODE* cur = new_node("CompSt", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
};

StmtList: Stmt StmtList {
        NODE* cur = new_node("StmtList", 1, NON_TER, $1->lineno);
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
        NODE* cur = new_node("Stmt", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }

    | IF LP Exp RP CloseStmt ELSE OpenStmt {
        NODE* cur = new_node("Stmt", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }

    | FOR LP NullableExp SEMI NullableExp SEMI NullableExp RP OpenStmt {
        NODE* cur = new_node("Stmt", 3, NON_TER, $1->lineno);
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
        NODE* cur = new_node("Stmt", 4, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }
    | IF LP Exp error Stmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | IF LP error RP Stmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Expression", "");
    }
    | IF LP Exp error CloseStmt ELSE OpenStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | IF LP error RP CloseStmt ELSE OpenStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Expression", "");
    }
    | WHILE LP error RP OpenStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Expression", "");
    }
    | WHILE LP Exp error OpenStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    };

CloseStmt: NullableExp SEMI {
        NODE* cur = new_node("Stmt", 5, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }

    | CompSt {
        NODE* cur = new_node("Stmt", 6, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | RETURN Exp SEMI {        
        NODE* cur = new_node("Stmt", 7, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | IF LP Exp RP CloseStmt ELSE CloseStmt {
        NODE* cur = new_node("Stmt", 8, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        insert(cur, $6);
        insert(cur, $7);
        $$ = cur;
    }

    | FOR LP NullableExp SEMI NullableExp SEMI NullableExp RP CloseStmt {
        NODE* cur = new_node("Stmt", 9, NON_TER, $1->lineno);
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
        NODE* cur = new_node("Stmt", 10, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        insert(cur, $5);
        $$ = cur;
    }    
    | RETURN Exp error SEMI {     
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");   
    }
    | RETURN Exp error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
        
    }
    | Exp error SEMI {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
    }
    | Exp error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
        
    }
    | IF LP Exp error CloseStmt ELSE CloseStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");   
    }
    | IF LP error RP CloseStmt ELSE CloseStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Expression", "");   
    }
    | WHILE LP error RP CloseStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Expression", "");   
    }
    | WHILE LP Exp error CloseStmt {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");   
    };



/* Internal Definition */
DefList: Def DefList {
        NODE* cur = new_node("DefList", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | %empty { 
        $$ = NULL;
    };
    
Def: Specifier DecList SEMI {
        NODE* cur = new_node("Def", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | error DecList SEMI {
        add_err(ErrorType::SYNTAX, yylineno, "Missing Specifier", "");
    }
    | Specifier DecList error SEMI {
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
    }    
    | Specifier DecList error RC {
        unput('}');
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Semicolon", "");
        
    };
DecList: Dec {
        NODE* cur = new_node("DecList", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | Dec COMMA DecList {
        NODE* cur = new_node("DecList", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
Dec: VarDec {
        NODE* cur = new_node("Dec", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
}
    | VarDec ASSIGN Exp{
        NODE* cur = new_node("Dec", 2, NON_TER, $1->lineno);
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

NullableExp: %empty { $$ = new_node("Null", 0, NON_TER, yylineno); }
    | Exp;

Exp: Exp BinaryOp_1 Exp {
        NODE* cur = new_node("Exp", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp BinaryOp_2 Exp {
        NODE* cur = new_node("Exp", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp MINUS Exp {
        NODE* cur = new_node("Exp", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp BinaryOp_3 Exp {
        NODE* cur = new_node("Exp", 3, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp ASSIGN Exp {
        NODE* cur = new_node("Exp", 4, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp AND Exp {
        NODE* cur = new_node("Exp", 5, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp OR Exp {
        NODE* cur = new_node("Exp", 6, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | MINUS Exp %prec UMINUS {
        NODE* cur = new_node("Exp", 7, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | NOT Exp {
        NODE* cur = new_node("Exp", 8, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        $$ = cur;
    }
    | EID LP Args RP {
        NODE* cur = new_node("Exp", 9, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | EID LP RP {
        NODE* cur = new_node("Exp", 10, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | Exp LB Exp RB {
        NODE* cur = new_node("Exp", 11, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        insert(cur, $4);
        $$ = cur;
    }
    | Exp DOT EID {
        NODE* cur = new_node("Exp", 12, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | LP Exp RP {
        NODE* cur = new_node("Exp", 13, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    }
    | EID {
        NODE* cur = new_node("Exp", 14, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | FLOAT {
        NODE* cur = new_node("Exp", 15, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | CHAR {
        NODE* cur = new_node("Exp", 16, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | INT {
        NODE* cur = new_node("Exp", 17, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | EID LP Args error ExpSuffix {
        yyless(strlen($5->node_val));
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis", "");
    }
    | EID LP error ExpSuffix {
        yyless(strlen($4->node_val));
        add_err(ErrorType::SYNTAX, $1->lineno, "Missing Right Parenthesis.", "");
    }    
    | Exp ERR Exp {
        
    };
Args: Exp {
        NODE* cur = new_node("Args", 1, NON_TER, $1->lineno);
        insert(cur, $1);
        $$ = cur;
    }
    | Exp COMMA Args{
        NODE* cur = new_node("Args", 2, NON_TER, $1->lineno);
        insert(cur, $1);
        insert(cur, $2);
        insert(cur, $3);
        $$ = cur;
    };
EID: ID
    | ERR {
        $$ = new_node("Null", 0, NON_TER, $1->lineno);
    }

%%
int main(int argc,char *argv[])
{
    std::fstream fin, fout;
    std::string path = std::string(argv[1]);
    fin.open(argv[1]);

    std::string out = path.substr(0, path.length()-3) + "out";
    fout.open(out, std::ios::out);
    freopen(out.c_str(), "w", stdout);

    auto token = into_lines(fin);
    token = file_inclusion(token);
    std::string proc_input = to_str(token);
    yy_switch_to_buffer(yy_scan_string(proc_input.c_str()));
    yyparse();

    IRList irs = semantic_analysis(get_root());
    for (auto i : irs) {
        std::cout << i.str() << std::endl;
    }
    return 0;
}