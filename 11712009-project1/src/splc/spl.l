%option yylineno
%{
    #include "spl.tab.h"
    #include "../ext/node.h"
    #include "../ext/ce.h"
    extern "C" int yylex();
%}

alpha [a-zA-Z]
digit [0-9]
nonzero [1-9]
hexdigit [0-9a-fA-F]
nonzerohex [1-9a-fA-F]
hexpre (0x)|(0X)
hexcharpre "\\x"|"\\X"
nonhex [g-zG-Z]
alphanum [0-9A-Za-z]
int "0"|({nonzero}{digit}*)

%x C_MULTILINE_COMMENT
%x C_SINGLELINE_COMMENT
%%

"//"  { BEGIN(C_SINGLELINE_COMMENT); }
<C_SINGLELINE_COMMENT>\n   { BEGIN(INITIAL); }
<C_SINGLELINE_COMMENT>[\t" "]   { }
<C_SINGLELINE_COMMENT>.    { }


"/*"  { BEGIN(C_MULTILINE_COMMENT); }
<C_MULTILINE_COMMENT>"*/" { BEGIN(INITIAL); }
<C_MULTILINE_COMMENT>[\n\t" "]   { }
<C_MULTILINE_COMMENT>.    { }


\n { }
[" "\t] { }

"int"|"float"|"char" {
    yylval.node = new_leaf("TYPE", yytext, TYPE, yylineno);
    return TYPE;
}

"struct" {
    yylval.node = new_leaf("STRUCT", yytext, STRUCT, yylineno);
    return STRUCT;
}

"if" {
    yylval.node = new_leaf("IF", yytext, IF, yylineno);
    return IF; 
}

"else" {
    
    yylval.node = new_leaf("ELSE", yytext, ELSE, yylineno);
    return ELSE;
}

"while" {
    yylval.node = new_leaf("WHILE", yytext, WHILE, yylineno);
    return WHILE;
}

"for" {
    yylval.node = new_leaf("FOR", yytext, FOR, yylineno);
    return FOR;
}

"return" {
    yylval.node = new_leaf("RETURN", yytext, RETURN, yylineno);
    return RETURN;
}

"." {
    
    yylval.node = new_leaf("DOT", yytext, DOT, yylineno);
    return DOT;
}
";" {
    
    yylval.node = new_leaf("SEMI", yytext, SEMI, yylineno);
    return SEMI;
}
"," {
    
    yylval.node = new_leaf("COMMA", yytext, COMMA, yylineno);
    return COMMA;
}
"=" {
    
    yylval.node = new_leaf("ASSIGN", yytext, ASSIGN, yylineno);
    return ASSIGN;
}
"<" {
    
    yylval.node = new_leaf("LT", yytext, LT, yylineno); 
    return BinaryOp_1;
}
"<=" {
    
        yylval.node = new_leaf("LE", yytext, LE, yylineno);
    return BinaryOp_1;
}
">" {
    
    yylval.node = new_leaf("GT", yytext, GT, yylineno);
    return BinaryOp_1;
}
">=" {
    
    yylval.node = new_leaf("GE", yytext, GE, yylineno);
    return BinaryOp_1;
}
"!=" {
    
    yylval.node = new_leaf("NE", yytext, NE, yylineno);
    return BinaryOp_1;
    }
"==" {
    
    yylval.node = new_leaf("EQ", yytext, EQ, yylineno);
    return BinaryOp_1;
}
"+" {
    
    yylval.node = new_leaf("PLUS", yytext, PLUS, yylineno);
    return BinaryOp_2;
}
"-" {
    
    yylval.node = new_leaf("MINUS", yytext, MINUS, yylineno);
    return MINUS;
}
"*" {
    
    yylval.node = new_leaf("MUL", yytext, MUL, yylineno);
    return BinaryOp_3;
}
"/" {
    
    yylval.node = new_leaf("DIV", yytext, DIV, yylineno);
    return BinaryOp_3;
}
"&&" {
    
    yylval.node = new_leaf("AND", yytext, AND, yylineno);
    return AND;
}
"||" {
    yylval.node = new_leaf("OR", yytext, OR, yylineno);
    return OR;
}
"!" {

    yylval.node = new_leaf("NOT", yytext, NOT, yylineno);
    return NOT;
}
"(" {
    
    yylval.node = new_leaf("LP", yytext, LP, yylineno);
    return LP;
}
")" {
    
    yylval.node = new_leaf("RP", yytext, RP, yylineno);
    return RP;
}
"[" {
    
    yylval.node = new_leaf("LB", yytext, LB, yylineno);
    return LB;
}
"]" {
    
    yylval.node = new_leaf("RB", yytext, RB, yylineno);
    return RB;
}
"{" {
    
    yylval.node = new_leaf("LC", yytext, LC, yylineno);
    return LC;
}
"}" {
    
    yylval.node = new_leaf("RC", yytext, RC, yylineno);
    return RC;
}

({alpha}|_)({alpha}|{digit}|_)* {
    yylval.node = new_leaf("ID", yytext, ID, yylineno); 
    return ID; 
}

"0"|({nonzero}{digit}*) { 
    yylval.node = new_leaf("INT", yytext, INT, yylineno);
    return INT;
}

{hexpre}("0"|({nonzerohex}{hexdigit}*)) { 
    int val = (int)strtol(yytext, NULL, 16);
    char buf[100];
    sprintf(buf, "%d", val);
    yylval.node = new_leaf("INT", buf, INT, yylineno);
    return INT;
}

{int}"."{digit}+ {
    yylval.node = new_leaf("FLOAT", yytext, FLOAT, yylineno);
    return FLOAT;
}

'.' { 
    yylval.node = new_leaf("CHAR", yytext, CHAR, yylineno);
    return CHAR;
}
'{hexcharpre}({hexdigit}{1,2})' {
    yylval.node = new_leaf("CHAR", yytext, CHAR, yylineno);
    return CHAR;
}

{hexpre}"0"{alphanum}+ {
    add_err(LEX, yylineno, "Leading Zero Inside Literal", yytext);
    yylval.node = new_leaf("INT", 0, INT, yylineno);
    return INT;
}

"0"{digit}+ { 
    add_err(LEX, yylineno, "Leading Zero Inside Literal", yytext);
    yylval.node = new_leaf("INT", 0, INT, yylineno);
    return INT;
}

{hexpre}(({nonzerohex}({hexdigit}*{nonhex}+)*)) {
    add_err(LEX, yylineno, "Invalid Hex", yytext);
    yylval.node = new_leaf("INT", 0, INT, yylineno);
    return INT;
}

'{hexcharpre}({hexdigit}|{nonhex})*' {
    add_err(LEX, yylineno, "Invalid Hex Char", yytext);
    yylval.node = new_leaf("CHAR", 0, CHAR, yylineno);
    return CHAR;
}

{digit}+({alpha}|_|{digit})+ {
    add_err(LEX, yylineno, "Invalid Identifier", yytext);
    yylval.node = new_leaf("ID", yytext, ID, yylineno);
    return ID;
}

. {
    add_err(LEX, yylineno, "Invalid Character", yytext);
    return ERR;
}


