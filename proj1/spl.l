%option yylineno
%{
    #include "spl.tab.h"
    #include "node.h"
%}

alpha [a-zA-Z]
digit [0-9]
nonzero [1-9]
hexdigit [0-9a-fA-F]
nonzerohex [1-9a-fA-F]
hexpre (0x)|(0X)
nonhex [g-zG-Z]
alphanum [0-9A-Za-z]

int "0"|({nonzero}{digit}*)
%%
\n { }
{alpha}({digit}_{alpha})* { 
    yylval.node = new_node((NODE_VAL)yytext, ID, yylineno); 
    return ID; 
}

"0"|({nonzero}{digit}*) { 
    yylval.node = new_node((NODE_VAL)yytext, INT, yylineno);
    return INT;
}
{hexpre}("0"|({nonzerohex}{hexdigit}*)) { 
    int int_val = (int)strtol(yytext, NULL, 16);
    yylval.node = new_node((NODE_VAL)int_val, INT, yylineno);
    return INT;
}

{int}"."{digit} {
    float float_val = atof(yytext);
    yylval.node = new_node((NODE_VAL)float_val, FLOAT, yylineno);
    return FLOAT;
}

'{alphanum}' { 
    yylval.node = new_node((NODE_VAL)yytext[1], CHAR, yylineno);
    return CHAR;
}
'{hexpre}{hexdigit}{2}' { 
    char hex_val = (char)strtol(yytext, NULL, 16);
    yylval.node = new_node((NODE_VAL)hex_val, CHAR, yylineno);
    return CHAR;
}

{digit}+({alpha}_{digit})+ { return NID;}

{hexpre}"0"{alphanum}+ {return LEADING_ZERO;}
"0"{digit}+ { return LEADING_ZERO;}

{hexpre}(({nonzerohex}({hexdigit}*{nonhex}+)*)) { return NONHEX;}

"int"|"float"|"char" {
    yylval.node = new_node((NODE_VAL)yytext, TYPE, yylineno);
    return TYPE;
}
"struct" {
    yylval.node = new_node((NODE_VAL)"STRUCT", STRUCT, yylineno);
    return STRUCT;
}
"if" { 
    yylval.node = new_node((NODE_VAL)"IF", IF, yylineno);
    return IF; 
}
"else" {
    yylval.node = new_node((NODE_VAL)"ELSE", ELSE, yylineno);
    return ELSE;
}
"while" {
    yylval.node = new_node((NODE_VAL)"WHILE", WHILE, yylineno);
    return WHILE;
}
"return" {
    yylval.node = new_node((NODE_VAL)"RETURN", RETURN, yylineno);
    return RETURN;
}
"." {    
    yylval.node = new_node((NODE_VAL)"DOT", DOT, yylineno);
    return DOT;
}
";" {
    yylval.node = new_node((NODE_VAL)"SEMI", SEMI, yylineno);
    return SEMI;
}
"," {
    yylval.node = new_node((NODE_VAL)"COMMA", COMMA, yylineno);
    return COMMA;
}
"=" {
    yylval.node = new_node((NODE_VAL)"ASSIGN", ASSIGN, yylineno);
    return ASSIGN;
}
"<" {
    yylval.node = new_node((NODE_VAL)"LT", LT, yylineno); 
    return LT;
}
"<=" {
        yylval.node = new_node((NODE_VAL)"LE", LE, yylineno);
    return LE;
}
">" {
    yylval.node = new_node((NODE_VAL)"GT", GT, yylineno);
    return GT;
}
">=" {
    yylval.node = new_node((NODE_VAL)"GE", GE, yylineno);
    return GE;
}
"!=" {
        yylval.node = new_node((NODE_VAL)"NE", NE, yylineno);
    return NE;
    }
"==" {    
    yylval.node = new_node((NODE_VAL)"EQ", EQ, yylineno);
    return EQ;
}
"+" {
    yylval.node = new_node((NODE_VAL)"PLUS", PLUS, yylineno);
    return PLUS;
}
"-" {
    yylval.node = new_node((NODE_VAL)"MINUS", MINUS, yylineno);
    return MINUS;
}
"*" {
    yylval.node = new_node((NODE_VAL)"MUL", MUL, yylineno);
    return MUL;
}
"/" {
    yylval.node = new_node((NODE_VAL)"DIV", DIV, yylineno);
    return DIV;
}
"&&" {
    yylval.node = new_node((NODE_VAL)"AND", AND, yylineno);
    return AND;
}
"||" {
    yylval.node = new_node((NODE_VAL)"OR", OR, yylineno);
    return OR;
}
"!" {
    yylval.node = new_node((NODE_VAL)"NOT", NOT, yylineno);
    return NOT;
}
"(" {
    yylval.node = new_node((NODE_VAL)"LP", LP, yylineno);
    return LP;
}
")" {
    yylval.node = new_node((NODE_VAL)"RP", RP, yylineno);
    return RP;
}
"[" {
    yylval.node = new_node((NODE_VAL)"LB", LB, yylineno);
    return LB;
}
"]" {
    yylval.node = new_node((NODE_VAL)"RB", RB, yylineno);
    return RB;
}
"{" {
    yylval.node = new_node((NODE_VAL)"LC", LC, yylineno);
    return LC;
}
"}" {
    yylval.node = new_node((NODE_VAL)"RC", RC, yylineno);
    return RC;
}

