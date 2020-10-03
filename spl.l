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
\n {  }

{alpha}({digit}_{alpha})* { 
    yylval.node = new_node((NODE_VAL)yytext, ID, yylineno); 
    return ID; 
}

{digit}+({alpha}_{digit})+ { return NID;}

"0"|({nonzero}{digit}*) { return INT;}
{hexpre}("0"|({nonzerohex}{hexdigit}*)) { return INT;}

{hexpre}"0"{alphanum}+ {return LEADING_ZERO;}
"0"{digit}+ { return LEADING_ZERO;}

{hexpre}(({nonzerohex}({hexdigit}*{nonhex}+)*)) { return NONHEX;}

{int}"."{digit} {return FLOAT;}

'{alphanum}' {  return CHAR;}
'{hexpre}{hexdigit}{2}' { return CHAR;}
"int"|"float"|"char" {

    return TYPE;
}
"struct" {return STRUCT;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"return" {return RETURN;}
"." {return DOT;}
";" {return SEMI;}
"," {return COMMA;}
"=" {return ASSIGN;}
"<" {return LT;}
"<=" {return LE;}
">" {return GT;}
">=" {return GE;}
"!=" {return NE;}
"==" {return EQ;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return LC;}
"}" {return RC;}

