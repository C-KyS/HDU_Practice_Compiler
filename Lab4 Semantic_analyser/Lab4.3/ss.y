%require "3.0"
%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "ast.h"
int yylex();
void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;
Node *root = nullptr;
enum PendingErrorKind {
    ERROR_NONE = 0,
    ERROR_MISSING_RBRACK,
    ERROR_MISSING_SEMI
};
PendingErrorKind pending_error = ERROR_NONE;
bool has_parse_error = false;
bool has_lex_error = false;
%}

%locations
%union {
    std::string *str;
    Node        *node;
}
%token <str> INTTK FLOATTK VOIDTK ID INTCON OCTCON HEXCON STRCON CHARCON
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token EQL
%type <node> CompUnit FuncDef Block BlockItem BlockItemList Decl VarDecl BType VarDef Stmt Exp Number
%type <node> AddExp MulExp PrimaryExp LVal VarArray
%left EQL
%left '+'
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
CompUnit : FuncDef               { root=$1; }
         ;
FuncDef : INTTK ID '(' ')' Block
        {
             $$ = new Node("FuncDef",@1.first_line);
             Node *funcType = new Node("FuncType",@1.first_line);
             funcType->child.push_back(new Node("Type",0,*$1));
             $$->child.push_back(funcType);
             $$->child.push_back(new Node("Ident",0,*$2)); // AST 节点名修改为 Ident
             $$->child.push_back(new Node("LPARENT",0));
             $$->child.push_back(new Node("RPARENT",0));
             $$->child.push_back($5);
        }
        ;
Block   : '{' BlockItemList '}' // 【修复】使用 BlockItemList
        {
             $$ = new Node("Block",@1.first_line);
             $$->child.push_back(new Node("LBRACE",0));
             for(auto c : $2->child) $$->child.push_back(c);
             $$->child.push_back(new Node("RBRACE",0));
             delete $2;
        }
        ;
// BlockItemList 规则，支持多个语句/声明
BlockItemList
        : BlockItemList BlockItem 
        {
            $$ = $1;
            $$->child.push_back($2);
        }
        | /* empty */
        {
            $$ = new Node("BlockItemList",0);
        }
        ;
BlockItem: Decl
        {
            $$ = new Node("BlockItem",$1->line);
            $$->child.push_back($1);
        }
        | Stmt
        {
            $$ = new Node("BlockItem",$1->line);
            $$->child.push_back($1);
        }
         ;
Decl    : VarDecl              { $$=$1; }
        ;
VarDecl : BType VarDef ';'
        {
             $$ = new Node("Decl",@1.first_line); // AST 节点名修改为 Decl
             $$->child.push_back(new Node("VarDecl",@1.first_line));
             $$->child.back()->child.push_back($1);
             $$->child.back()->child.push_back($2);
             $$->child.back()->child.push_back(new Node("SEMICN",0));
        }
        ;
BType   : INTTK
        {
             $$ = new Node("BType",@1.first_line);
             $$->child.push_back(new Node("Type",0,*$1));
        }
        ;
VarDef  : ID
        {
             $$ = new Node("VarDef",@1.first_line);
             $$->child.push_back(new Node("Ident",0,*$1)); // AST 节点名修改为 Ident
        }
        | ID VarArray
        {
             $$ = new Node("VarDef",@1.first_line);
             $$->child.push_back(new Node("Ident",0,*$1));
             for(auto c : $2->child) $$->child.push_back(c);
             delete $2;
        }
        | ID '=' Exp
        {
             $$ = new Node("VarDef",@1.first_line);
             $$->child.push_back(new Node("Ident",0,*$1)); // AST 节点名修改为 Ident
             $$->child.push_back(new Node("ASSIGN",0));
             Node *init = new Node("InitVal",$3->line);
             init->child.push_back($3);
             $$->child.push_back(init);
        }
        | ID VarArray '=' Exp
        {
             $$ = new Node("VarDef",@1.first_line);
             $$->child.push_back(new Node("Ident",0,*$1));
             for(auto c : $2->child) $$->child.push_back(c);
             $$->child.push_back(new Node("ASSIGN",0));
             Node *init = new Node("InitVal",$4->line);
             init->child.push_back($4);
             $$->child.push_back(init);
             delete $2;
        }
        ;
VarArray: VarArray '[' Number ']'
        {
             $$ = $1;
             $$->child.push_back(new Node("LBRACK",0));
             $$->child.push_back($3);
             $$->child.push_back(new Node("RBRACK",0));
        }
        | '[' Number ']'
        {
             $$ = new Node("ArrayDims",0);
             $$->child.push_back(new Node("LBRACK",0));
             $$->child.push_back($2);
             $$->child.push_back(new Node("RBRACK",0));
        }
        | '[' Number
        {
             pending_error = ERROR_MISSING_RBRACK;
        }
        error
        {
             has_parse_error = true;
             int line = $2 ? $2->line : yylineno;
             printf("Error type B at Line %d: Missing \"]\".\n",line);
             pending_error = ERROR_NONE;
             yyerrok;
             yyclearin;
             $$ = new Node("ArrayDims",0);
             $$->child.push_back(new Node("LBRACK",0));
             $$->child.push_back($2);
        }
        ;
Stmt    : LVal '=' Exp ';'
        {
             $$ = new Node("Stmt",@1.first_line);
             $$->child.push_back($1);
             $$->child.push_back(new Node("ASSIGN",0));
             $$->child.push_back($3);
             $$->child.push_back(new Node("SEMICN",0));
        }
        | Block
        {
             $$ = new Node("Stmt",@1.first_line);
             $$->child.push_back($1);
        }
        | LVal '=' Exp
        {
             pending_error = ERROR_MISSING_SEMI;
        }
        error
        {
             has_parse_error = true;
             int line = $3 ? $3->line : yylineno;
             printf("Error type B at Line %d: Missing \";\".\n",line);
             pending_error = ERROR_NONE;
             yyerrok;
             yyclearin;
        }
        | IF '(' Exp ')' Stmt %prec LOWER_THAN_ELSE
        {
             $$ = new Node("Stmt",@1.first_line);
             Node *ifNode = new Node("IfStmt",@1.first_line);
             ifNode->child.push_back(new Node("IF",0));
             ifNode->child.push_back(new Node("LPARENT",0));
             ifNode->child.push_back($3);
             ifNode->child.push_back(new Node("RPARENT",0));
             ifNode->child.push_back($5);
             $$->child.push_back(ifNode);
        }
        | IF '(' Exp ')' Stmt ELSE Stmt
        {
             $$ = new Node("Stmt",@1.first_line);
             Node *ifNode = new Node("IfStmt",@1.first_line);
             ifNode->child.push_back(new Node("IF",0));
             ifNode->child.push_back(new Node("LPARENT",0));
             ifNode->child.push_back($3);
             ifNode->child.push_back(new Node("RPARENT",0));
             ifNode->child.push_back($5);
             ifNode->child.push_back(new Node("ELSE",0));
             ifNode->child.push_back($7);
             $$->child.push_back(ifNode);
        }
        ;
Exp     : AddExp
        {
             $$ = new Node("Exp",$1->line);
             $$->child.push_back($1);
        }
        | Exp EQL AddExp
        {
             $$ = new Node("Exp",@2.first_line);
             $$->child.push_back($1);
             $$->child.push_back(new Node("EQL",0,"=="));
             $$->child.push_back($3);
        }
        ;
AddExp  : MulExp               { $$=$1; }
        | AddExp '+' MulExp
        {
             $$ = new Node("AddExp",@1.first_line);
             $$->child.push_back($1);
             $$->child.push_back(new Node("PLUS",0,"+")); // 【修复】传入行号
             $$->child.push_back($3);
        }
        ;
MulExp  : PrimaryExp           { $$=$1; }
        ;
PrimaryExp: Number             { $$=$1; }
          | LVal
            {
                $$ = new Node("PrimaryExp",@1.first_line);
                $$->child.push_back($1);
            }
          ;
LVal    : ID
        {
             $$ = new Node("LVal",@1.first_line);
             $$->child.push_back(new Node("Ident",0,*$1));
        }
        | LVal '[' Exp ']'
        {
             $$ = $1;
             $$->child.push_back(new Node("LBRACK",0));
             $$->child.push_back($3);
             $$->child.push_back(new Node("RBRACK",0));
        }
        | LVal '[' Exp ',' Exp ']'
        {
             has_parse_error = true;
             int line = $3 ? $3->line : yylineno;
             printf("Error type B at Line %d: Missing \"]\".\n",line);
             delete $3;
             delete $5;
             $$ = $1;
        }
        | LVal '[' Exp
        {
             pending_error = ERROR_MISSING_RBRACK;
        }
        error
        {
             has_parse_error = true;
             int line = $3 ? $3->line : yylineno;
             printf("Error type B at Line %d: Missing \"]\".\n",line);
             pending_error = ERROR_NONE;
             yyerrok;
             yyclearin;
             $$ = $1;
        }
        ;
Number  : INTCON
        {
             $$ = new Node("Number",@1.first_line);
             $$->child.push_back(new Node("INTCON",0,*$1));
        }
        | OCTCON
        {
             $$ = new Node("Number",@1.first_line);
             $$->child.push_back(new Node("INTCON",0,*$1)); /* 词法已转 10 进制 */
        }
        | HEXCON
        {
             $$ = new Node("Number",@1.first_line);
             $$->child.push_back(new Node("INTCON",0,*$1));
        }
        ;
%%

void yyerror(const char *s){
    has_parse_error = true;
    if(has_lex_error) return;
    if(pending_error != ERROR_NONE) return;
    printf("Error type B at Line %d: %s\n",yylineno,s);
}

/* ... Node::print 和 main 函数不变 ... */

/* 先序打印，简单缩进 */
void Node::print(int dep){
    for(int i=0;i<dep;i++) putchar(' ');
    printf("%s",name.c_str());
    if(line) printf(" (%d)",line);
    if(!attr.empty()) printf(": %s",attr.c_str());
    putchar('\n');
    for(auto c:child) c->print(dep+2);
}
/* main 统一入口 */
int main(int argc,char **argv){
    if(argc<2){fprintf(stderr,"Usage: %s <file.sy>\n",argv[0]); return 1;}
    FILE *f=fopen(argv[1],"r");
    if(!f){perror(argv[1]); return 1;}
    yyin=f;
    has_parse_error = false;
    has_lex_error = false;
    pending_error = ERROR_NONE;
    root = nullptr;
    
    // 【修改】只有在 yyparse() 成功时 (返回 0) 才打印 AST
    if(!yyparse() && !has_parse_error && !has_lex_error && root) root->print(); 
    
    fclose(f);
    return 0;
}