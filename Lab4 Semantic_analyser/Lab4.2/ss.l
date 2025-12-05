%{
/* 用 C++ 输出也行，这里用最简 C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lineno = 1;          // 当前行号
FILE *out = NULL;        // 如想输出到文件可改

/* 把 8/16 进制字符串转 10 进制并打印 */
void print_intcon(char *text, int base) {
    long v = strtol(text, NULL, base);
    printf("INTCON %ld\n", v);
}

/* 统一错误出口 */
void err(char *msg) {
    printf("Error type A at line %d:%s\n", lineno, msg);
}

/* 非法数字错误出口 */
void err_number(char *msg, char *number) {
    printf("Error type A at line %d: %s '%s'\n", lineno, msg, number);
}
%}

%option noyywrap
%option yylineno
%%

"int"                   { printf("INTTK int\n"); }
"float"                 { printf("FLOATTK float\n"); }   /* 选做 */
"void"                  { printf("VOIDTK void\n"); }
"if"                    { printf("IFTK if\n"); }
"else"                  { printf("ELSETK else\n"); }
"while"                 { printf("WHILETK while\n"); }
"break"                 { printf("BREAKTK break\n"); }
"continue"              { printf("CONTINUETK continue\n"); }
"return"                { printf("RETURNTK return\n"); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("ID %s\n", yytext); }

0[0-9]*[89]             { err_number("Illegal octal number", yytext); }
0[xX][0-9a-fA-F]+[g-zG-Z] { err_number("Illegal hexadecimal number", yytext); }
0[xX][0-9a-fA-F]+       { print_intcon(yytext, 16); }
0[0-7]+                 { print_intcon(yytext, 8); }
0                       { print_intcon(yytext, 10); }
[1-9][0-9]*             { print_intcon(yytext, 10); }

\"(\\.|[^\\"])*\"        { printf("STRCON %s\n", yytext); }  /* 字符串常量 */
\'(\\.|[^\\'])\'         { printf("CHARCON %s\n", yytext); }  /* 字符常量 */

"("                     { printf("LPARENT (\n"); }
")"                     { printf("RPARENT )\n"); }
"["                     { printf("LBRACK [\n"); }
"]"                     { printf("RBRACK ]\n"); }
"{"                     { printf("LBRACE {\n"); }
"}"                     { printf("RBRACE }\n"); }

"+"                     { printf("PLUS +\n"); }
"-"                     { printf("MINUS -\n"); }
"*"                     { printf("MULT *\n"); }
"/"                     { printf("DIV /\n"); }
"%"                     { printf("MOD %%\n"); }
"="                     { printf("ASSIGN =\n"); }
"=="                    { printf("EQL ==\n"); }
"!="                    { printf("NEQ !=\n"); }
"<"                     { printf("LSS <\n"); }
"<="                    { printf("LEQ <=\n"); }
">"                     { printf("GRE >\n"); }
">="                    { printf("GEQ >=\n"); }
"!"                     { printf("NOT !\n"); }
"&&"                    { printf("AND &&\n"); }
"||"                    { printf("OR ||\n"); }

";"                     { printf("SEMICN ;\n"); }
","                     { printf("COMMA ,\n"); }

[ \t\r]+                { /* 空白忽略 */ }
\n                      { lineno++; }

.                       { char buf[128];
                          snprintf(buf, sizeof(buf), "Invalid character '%s'", yytext);
                          err(buf); }
%%
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.sy>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 1;
    }
    yyin = f;
    yylex();
    fclose(f);
    return 0;
}