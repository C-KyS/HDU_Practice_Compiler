%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include "ast.h"
#include "ss.tab.h"    // Bison 生成的 token 编码
extern int yylineno;
extern Node *root;      // 语法树根，Bison 里赋值
extern YYLTYPE yylloc;
extern bool has_lex_error;
#define YY_USER_ACTION \
    do { yylloc.first_line = yylineno; yylloc.last_line = yylineno; } while(0);

static std::string to_decimal(const char *text, int base){
    long long val = strtoll(text,nullptr,base);
    return std::to_string(val);
}
static void report_lex_error(const char *msg, const char *lexeme){
    printf("Error type A at Line %d: %s \"%s\"\n", yylineno, msg, lexeme);
    has_lex_error = true;
}
%}

%option noyywrap yylineno

%%
[ \t\r]+                 { /* 空白 */ }
\n                       { /* yylineno 会自动 ++ */ }

"int"                    { yylval.str = new std::string("int");   return INTTK; }
"float"                  { yylval.str = new std::string("float"); return FLOATTK; }
"void"                   { yylval.str = new std::string("void");  return VOIDTK; }
"if"                     { return IF; }
"else"                   { return ELSE; }
"while"                  { return WHILE; }
"break"                  { return BREAK; }
"continue"               { return CONTINUE; }
"return"                 { return RETURN; }

0[0-7]+                  { yylval.str = new std::string(to_decimal(yytext,8)); return OCTCON; }
0[xX][0-9a-fA-F]+        { yylval.str = new std::string(to_decimal(yytext,16)); return HEXCON; }
[1-9][0-9]*              { yylval.str = new std::string(yytext); return INTCON; }
0                        { yylval.str = new std::string("0"); return INTCON; } // 修复：缺失单独的 '0' 匹配

0[0-7]*[89][0-9a-zA-Z]*  {
                          report_lex_error("Illegal octal number", yytext);
                          yylval.str = new std::string("0");
                          return INTCON;
                        }
0[xX][0-9a-fA-F]*[g-zG-Z][0-9a-zA-Z]* {
                          report_lex_error("Illegal hexadecimal number", yytext);
                          yylval.str = new std::string("0");
                          return INTCON;
                        }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = new std::string(yytext); return ID; }

\"(\\.|[^\\"])*\"        { yylval.str = new std::string(yytext); return STRCON; }
\'(\\.|[^\\'])\'          { yylval.str = new std::string(yytext); return CHARCON; }

"("                      { return '('; }
")"                      { return ')'; }
"["                      { return '['; }
"]"                      { return ']'; }
"{"                      { return '{'; }
"}"                      { return '}'; }
";"                      { return ';'; }
","                      { return ','; }
"+"                      { return '+'; }
"-"                      { return '-'; }
"*"                      { return '*'; }
"/"                      { return '/'; }
"%"                      { return '%'; }
"=="                     { return EQL; }
"="                      { return '='; }

.                        { report_lex_error("Invalid character", yytext); return 0; }
%%