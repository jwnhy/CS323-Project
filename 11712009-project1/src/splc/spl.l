%option yylineno
%{
    #include "spl.tab.h"
    #include "../ext/node.h"
    #include "../ext/ce.h"
    extern "C" int yylex();
    int EOF_CNT = 0;
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
    yylval.node = new_node("TYPE", yytext, TYPE, yylineno);
    return TYPE;
}

"struct" {
    yylval.node = new_node("STRUCT", yytext, STRUCT, yylineno);
    return STRUCT;
}

"if" {
    yylval.node = new_node("IF", yytext, IF, yylineno);
    return IF; 
}

"else" {
    
    yylval.node = new_node("ELSE", yytext, ELSE, yylineno);
    return ELSE;
}

"while" {
    yylval.node = new_node("WHILE", yytext, WHILE, yylineno);
    return WHILE;
}

"for" {
    yylval.node = new_node("FOR", yytext, FOR, yylineno);
    return FOR;
}

"return" {
    yylval.node = new_node("RETURN", yytext, RETURN, yylineno);
    return RETURN;
}

"." {
    
    yylval.node = new_node("DOT", yytext, DOT, yylineno);
    return DOT;
}
";" {
    
    yylval.node = new_node("SEMI", yytext, SEMI, yylineno);
    return SEMI;
}
"," {
    
    yylval.node = new_node("COMMA", yytext, COMMA, yylineno);
    return COMMA;
}
"=" {
    
    yylval.node = new_node("ASSIGN", yytext, ASSIGN, yylineno);
    return ASSIGN;
}
"<" {
    
    yylval.node = new_node("LT", yytext, LT, yylineno); 
    return BinaryOp_1;
}
"<=" {
    
        yylval.node = new_node("LE", yytext, LE, yylineno);
    return BinaryOp_1;
}
">" {
    
    yylval.node = new_node("GT", yytext, GT, yylineno);
    return BinaryOp_1;
}
">=" {
    
    yylval.node = new_node("GE", yytext, GE, yylineno);
    return BinaryOp_1;
}
"!=" {
    
    yylval.node = new_node("NE", yytext, NE, yylineno);
    return BinaryOp_1;
    }
"==" {
    
    yylval.node = new_node("EQ", yytext, EQ, yylineno);
    return BinaryOp_1;
}
"+" {
    
    yylval.node = new_node("PLUS", yytext, PLUS, yylineno);
    return BinaryOp_2;
}
"-" {
    
    yylval.node = new_node("MINUS", yytext, MINUS, yylineno);
    return BinaryOp_2;
}
"*" {
    
    yylval.node = new_node("MUL", yytext, MUL, yylineno);
    return BinaryOp_3;
}
"/" {
    
    yylval.node = new_node("DIV", yytext, DIV, yylineno);
    return BinaryOp_3;
}
"&&" {
    
    yylval.node = new_node("AND", yytext, AND, yylineno);
    return AND;
}
"||" {
    yylval.node = new_node("OR", yytext, OR, yylineno);
    return OR;
}
"!" {
    
    yylval.node = new_node("NOT", yytext, NOT, yylineno);
    return NOT;
}
"(" {
    
    yylval.node = new_node("LP", yytext, LP, yylineno);
    return LP;
}
")" {
    
    yylval.node = new_node("RP", yytext, RP, yylineno);
    return RP;
}
"[" {
    
    yylval.node = new_node("LB", yytext, LB, yylineno);
    return LB;
}
"]" {
    
    yylval.node = new_node("RB", yytext, RB, yylineno);
    return RB;
}
"{" {
    
    yylval.node = new_node("LC", yytext, LC, yylineno);
    return LC;
}
"}" {
    
    yylval.node = new_node("RC", yytext, RC, yylineno);
    return RC;
}

({alpha}|_)({alpha}|{digit}|_)* {
    yylval.node = new_node("ID", yytext, ID, yylineno); 
    return ID; 
}

"0"|({nonzero}{digit}*) { 
    yylval.node = new_node("INT", yytext, INT, yylineno);
    return INT;
}

{hexpre}("0"|({nonzerohex}{hexdigit}*)) { 
    int val = (int)strtol(yytext, NULL, 16);
    char buf[100];
    sprintf(buf, "%d", val);
    yylval.node = new_node("INT", buf, INT, yylineno);
    return INT;
}

{int}"."{digit}+ {
    yylval.node = new_node("FLOAT", yytext, FLOAT, yylineno);
    return FLOAT;
}

'.' { 
    yylval.node = new_node("CHAR", yytext, CHAR, yylineno);
    return CHAR;
}
'{hexcharpre}({hexdigit}{1,2})' {
    yylval.node = new_node("CHAR", yytext, CHAR, yylineno);
    return CHAR;
}

{hexpre}"0"{alphanum}+ {
    add_err(LEX, yylineno, "Leading Zero Inside Literal", yytext);
    yylval.node = new_node("INT", 0, INT, yylineno);
    return INT;
}

"0"{digit}+ { 
    add_err(LEX, yylineno, "Leading Zero Inside Literal", yytext);
    yylval.node = new_node("INT", 0, INT, yylineno);
    return INT;
}

{hexpre}(({nonzerohex}({hexdigit}*{nonhex}+)*)) {
    add_err(LEX, yylineno, "Invalid Hex", yytext);
    yylval.node = new_node("INT", 0, INT, yylineno);
    return INT;
}

'{hexcharpre}({hexdigit}|{nonhex})*' {
    add_err(LEX, yylineno, "Invalid Hex Char", yytext);
    yylval.node = new_node("CHAR", 0, CHAR, yylineno);
    return CHAR;
}

{digit}+({alpha}|_|{digit})+ {
    add_err(LEX, yylineno, "Invalid Identifier", yytext);
    yylval.node = new_node("ID", yytext, ID, yylineno);
    return ID;
}

. {
    add_err(LEX, yylineno, "Invalid Character", yytext);
    return ERR;
}


