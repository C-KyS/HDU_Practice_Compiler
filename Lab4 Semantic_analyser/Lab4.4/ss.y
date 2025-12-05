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

bool has_parse_error = false;
bool has_lex_error = false;
// 来自 semantic.cpp 的变量
extern bool has_semantic_error;
%}

%locations
%union {
    std::string *str;
    Node        *node;
}

%token <str> INTTK FLOATTK VOIDTK ID INTCON OCTCON HEXCON FLOATCON STRCON
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token EQL NEQ LEQ GEQ AND OR

%type <node> CompUnit FuncDef Block BlockItemList BlockItem Decl VarDecl BType VarDef InitVal VarDefList
%type <node> Stmt Exp LVal PrimaryExp UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp
%type <node> FuncFParams FuncFParam FuncRParams

%precedence LOWER_THAN_ELSE
%precedence ELSE

%%
CompUnit : CompUnit FuncDef { $$=$1; $$->child.push_back($2); }
         | CompUnit Decl    { $$=$1; $$->child.push_back($2); }
         | FuncDef          { root = new Node("CompUnit", @1.first_line); root->child.push_back($1); $$=root; }
         | Decl             { root = new Node("CompUnit", @1.first_line); root->child.push_back($1); $$=root; }
         ;

Decl     : VarDecl { $$=$1; } ;

VarDecl  : BType VarDefList ';' {
             $$ = new Node("VarDecl", @1.first_line);
             $$->child.push_back($1);
             for(auto c : $2->child) {
                 $$->child.push_back(c);
             }
         }
         ;

VarDefList : VarDef {
                $$ = new Node("VarDefList", @1.first_line);
                $$->child.push_back($1);
            }
            | VarDefList ',' VarDef {
                $$ = $1;
                $$->child.push_back($3);
            }
            ;

BType    : INTTK   { $$ = new Node("BType", @1.first_line); $$->child.push_back(new Node("Type",0,"int")); }
         | FLOATTK { $$ = new Node("BType", @1.first_line); $$->child.push_back(new Node("Type",0,"float")); }
         | VOIDTK  { $$ = new Node("BType", @1.first_line); $$->child.push_back(new Node("Type",0,"void")); }
         ;

VarDef   : ID {
             $$ = new Node("VarDef", @1.first_line);
             $$->child.push_back(new Node("Ident", @1.first_line, *$1));
         }
         | ID '=' InitVal {
             $$ = new Node("VarDef", @1.first_line);
             $$->child.push_back(new Node("Ident", @1.first_line, *$1));
             $$->child.push_back(new Node("ASSIGN", 0));
             $$->child.push_back($3);
         }
         | ID '[' Exp ']' { // 简化: 仅支持一维数组，多维类似
             $$ = new Node("VarDef", @1.first_line);
             $$->child.push_back(new Node("Ident", @1.first_line, *$1));
             Node* dims = new Node("ArrayDims", @2.first_line);
             dims->child.push_back($3);
             $$->child.push_back(dims);
         }
         ;

InitVal  : Exp { $$ = new Node("InitVal", @1.first_line); $$->child.push_back($1); } ;

FuncDef  : BType ID '(' ')' Block {
             $$ = new Node("FuncDef", @1.first_line);
             Node* ft = new Node("FuncType", @1.first_line);
             ft->child.push_back($1->child[0]); // Type
             $$->child.push_back(ft);
             $$->child.push_back(new Node("Ident", @2.first_line, *$2));
             $$->child.push_back($5);
         }
         | BType ID '(' FuncFParams ')' Block {
             $$ = new Node("FuncDef", @1.first_line);
             Node* ft = new Node("FuncType", @1.first_line);
             ft->child.push_back($1->child[0]);
             $$->child.push_back(ft);
             $$->child.push_back(new Node("Ident", @2.first_line, *$2));
             $$->child.push_back($4);
             $$->child.push_back($6);
         }
         ;

FuncFParams : FuncFParam { $$ = new Node("FuncFParams", @1.first_line); $$->child.push_back($1); }
            | FuncFParams ',' FuncFParam { $$=$1; $$->child.push_back($3); }
            ;

FuncFParam : BType ID {
               $$ = new Node("FuncFParam", @1.first_line);
               $$->child.push_back($1);
               $$->child.push_back(new Node("Ident", @2.first_line, *$2));
           }
           ;

Block    : '{' BlockItemList '}' {
             $$ = new Node("Block", @1.first_line);
             if($2) $$->child.push_back($2);
         }
         ;

BlockItemList : /* empty */ { $$ = nullptr; }
              | BlockItemList BlockItem {
                  if(!$1) $$ = new Node("BlockItemList", @2.first_line);
                  else $$ = $1;
                  $$->child.push_back($2);
              }
              ;

BlockItem : Decl { $$=$1; } | Stmt { $$=$1; } ;

Stmt      : LVal '=' Exp ';' {
              $$ = new Node("Stmt", @1.first_line);
              $$->child.push_back($1);
              $$->child.push_back(new Node("ASSIGN",0));
              $$->child.push_back($3);
          }
          | Exp ';' {
              $$ = new Node("Stmt", @1.first_line);
              $$->child.push_back($1); // 可能是函数调用语句
          }
          | Exp error ';' {
              // 错误恢复：遇到错误后插入分号，仍然构建Stmt节点
              // 这样可以在报告语法错误后继续语义分析
              $$ = new Node("Stmt", @1.first_line);
              $$->child.push_back($1);
          }
          | Exp error {
              // 错误恢复：遇到错误时（如缺少分号），仍然构建Stmt节点
              // 这样可以在报告语法错误后继续语义分析
              $$ = new Node("Stmt", @1.first_line);
              $$->child.push_back($1);
          }
          | Block { $$=$1; }
          | RETURN Exp ';' {
              $$ = new Node("Stmt", @1.first_line);
              Node* ret = new Node("Return", @1.first_line);
              ret->child.push_back($2);
              $$->child.push_back(ret);
          }
          | RETURN ';' {
              $$ = new Node("Stmt", @1.first_line);
              $$->child.push_back(new Node("Return", @1.first_line));
          }
          | IF '(' Exp ')' Stmt %prec LOWER_THAN_ELSE {
              $$ = new Node("IfStmt", @1.first_line);
              $$->child.push_back($3); $$->child.push_back($5);
          }
          | IF '(' Exp ')' Stmt ELSE Stmt {
              $$ = new Node("IfStmt", @1.first_line);
              $$->child.push_back($3); $$->child.push_back($5); $$->child.push_back($7);
          }
          | WHILE '(' Exp ')' Stmt {
              $$ = new Node("WhileStmt", @1.first_line);
              $$->child.push_back($3); $$->child.push_back($5);
          }
          | BREAK ';' { $$ = new Node("BreakStmt", @1.first_line); }
          | CONTINUE ';' { $$ = new Node("ContinueStmt", @1.first_line); }
          ;

Exp       : LOrExp { $$=$1; } ;
LOrExp    : LAndExp { $$=$1; } 
          | LOrExp OR LAndExp { $$=new Node("LOrExp",@1.first_line); $$->child.push_back($1); $$->child.push_back($3); } ;
LAndExp   : EqExp { $$=$1; }
          | LAndExp AND EqExp { $$=new Node("LAndExp",@1.first_line); $$->child.push_back($1); $$->child.push_back($3); } ;
EqExp     : RelExp { $$=$1; }
          | EqExp EQL RelExp { $$=new Node("EqExp",@1.first_line,"=="); $$->child.push_back($1); $$->child.push_back($3); }
          | EqExp NEQ RelExp { $$=new Node("EqExp",@1.first_line,"!="); $$->child.push_back($1); $$->child.push_back($3); } ;
RelExp    : AddExp { $$=$1; }
          | RelExp '<' AddExp { $$=new Node("RelExp",@1.first_line,"<"); $$->child.push_back($1); $$->child.push_back($3); }
          | RelExp '>' AddExp { $$=new Node("RelExp",@1.first_line,">"); $$->child.push_back($1); $$->child.push_back($3); } ;
AddExp    : MulExp { $$=$1; }
          | AddExp '+' MulExp { $$=new Node("AddExp",@1.first_line,"+"); $$->child.push_back($1); $$->child.push_back($3); }
          | AddExp '-' MulExp { $$=new Node("AddExp",@1.first_line,"-"); $$->child.push_back($1); $$->child.push_back($3); } ;
MulExp    : UnaryExp { $$=$1; }
          | MulExp '*' UnaryExp { $$=new Node("MulExp",@1.first_line,"*"); $$->child.push_back($1); $$->child.push_back($3); }
          | MulExp '/' UnaryExp { $$=new Node("MulExp",@1.first_line,"/"); $$->child.push_back($1); $$->child.push_back($3); } ;

UnaryExp  : PrimaryExp { $$=$1; }
          | ID '(' ')' {
              $$ = new Node("FuncCall", @1.first_line);
              $$->child.push_back(new Node("Ident", @1.first_line, *$1));
          }
          | ID '(' FuncRParams ')' {
              $$ = new Node("FuncCall", @1.first_line);
              $$->child.push_back(new Node("Ident", @1.first_line, *$1));
              $$->child.push_back($3);
          }
          | ID '(' FuncRParams error {
              // 错误恢复：允许缺少右括号的函数调用
              $$ = new Node("FuncCall", @1.first_line);
              $$->child.push_back(new Node("Ident", @1.first_line, *$1));
              $$->child.push_back($3);
          }
          | ID '(' error {
              // 错误恢复：允许缺少参数和右括号的函数调用
              $$ = new Node("FuncCall", @1.first_line);
              $$->child.push_back(new Node("Ident", @1.first_line, *$1));
          }
          ;

FuncRParams : Exp { $$ = new Node("FuncRParams", @1.first_line); $$->child.push_back($1); }
            | FuncRParams ',' Exp { $$=$1; $$->child.push_back($3); }
            ;

PrimaryExp : '(' Exp ')' { $$=$2; }
           | LVal { $$=$1; }
           | INTCON { $$ = new Node("Number", @1.first_line); $$->child.push_back(new Node("INTCON",0,*$1)); }
           | OCTCON { $$ = new Node("Number", @1.first_line); $$->child.push_back(new Node("INTCON",0,*$1)); }
           | HEXCON { $$ = new Node("Number", @1.first_line); $$->child.push_back(new Node("INTCON",0,*$1)); }
           | FLOATCON { $$ = new Node("Number", @1.first_line); $$->child.push_back(new Node("FLOATCON",0,*$1)); }
           ;

LVal      : ID {
              $$ = new Node("LVal", @1.first_line);
              $$->child.push_back(new Node("Ident", @1.first_line, *$1));
          }
          | LVal '[' Exp ']' {
              $$ = $1;
              $$->child.push_back(new Node("Index", @2.first_line)); // 标记下标
              $$->child.back()->child.push_back($3);
          }
          ;
%%

void yyerror(const char *s){
    has_parse_error = true;
    printf("Error type B at Line %d: %s\n", yylineno, s);
}

void Node::print(int dep){
    for(int i=0;i<dep;i++) putchar(' ');
    printf("%s",name.c_str());
    if(line) printf(" (%d)",line);
    if(!attr.empty()) printf(": %s",attr.c_str());
    putchar('\n');
    for(auto c:child) if(c) c->print(dep+2);
}

int main(int argc,char **argv){
    if(argc<2){fprintf(stderr,"Usage: %s <file.sy>\n",argv[0]); return 1;}
    FILE *f=fopen(argv[1],"r");
    if(!f){perror(argv[1]); return 1;}
    yyin=f;
    yyparse();
    
    // 即使有语法错误，如果AST已构建，也尝试进行语义分析以报告语义错误
    // 语法错误已经在yyerror中报告了
    if(!has_lex_error && root) {
        // 进行语义分析
        semantic_analysis(root);
        // 如果没有语义错误，可打印 AST 验证或输出 success（根据任务要求）
        // if(!has_semantic_error) printf("success\n");
    }
    fclose(f);
    return 0;
}