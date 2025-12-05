#include "ast.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

// 全局变量记录是否有语义错误
bool has_semantic_error = false;

struct Symbol
{
    string name;
    string kind; // "var", "func", "array"
    string type; // "int", "float", "void"
    bool isArray = false;
    int paramCount = 0; // 函数参数个数
    int definedLine;
    vector<string> paramTypes;
};

class Scope
{
public:
    unordered_map<string, Symbol> table;
};

class SemanticContext
{
public:
    vector<Scope> scopeStack;
    string currentFuncReturnType;
    int loopDepth = 0;

    SemanticContext()
    {
        enterScope(); // 全局作用域
    }
    void enterScope() { scopeStack.push_back(Scope()); }
    void exitScope() { scopeStack.pop_back(); }

    bool define(Symbol sym)
    {
        if (scopeStack.back().table.count(sym.name))
            return false;
        scopeStack.back().table[sym.name] = sym;
        return true;
    }

    Symbol *lookup(string name, bool currentScopeOnly = false)
    {
        if (currentScopeOnly)
        {
            if (scopeStack.back().table.count(name))
                return &scopeStack.back().table[name];
            return nullptr;
        }
        // 从内到外搜索作用域栈
        for (int i = static_cast<int>(scopeStack.size()) - 1; i >= 0; --i)
        {
            if (scopeStack[i].table.count(name))
                return &scopeStack[i].table[name];
        }
        return nullptr;
    }
};

SemanticContext ctx;

void reportError(int type, int line, string msg)
{
    // 如果已报告过语义错误，不再重复报告（只输出第一个语义错误）
    if (has_semantic_error)
        return;
    has_semantic_error = true;
    printf("Error type %d at Line %d: %s\n", type, line, msg.c_str());
}

string checkExp(Node *node);

// 新增：收集实参、统一处理函数调用
void collectCallArgs(Node *node, vector<Node *> &out)
{
    if (!node)
        return;
    // FuncRParams节点的子节点是Exp节点，需要递归收集
    // 如果节点名是FuncRParams，直接收集其所有子节点（这些子节点就是Exp节点）
    if (node->name == "FuncRParams")
    {
        for (auto child : node->child)
        {
            if (child)
            {
                // FuncRParams的子节点就是Exp节点，直接添加
                out.push_back(child);
            }
        }
        return;
    }
    // 如果节点名包含"Exp"（但不是"Index"和"FuncRParams"），说明这是一个表达式节点，应该收集
    if (node->name.find("Exp") != string::npos && node->name != "Index" && 
        node->name != "FuncRParams")
    {
        out.push_back(node);
        return;
    }
    // 对于其他节点，需要递归处理其子节点
    for (auto child : node->child)
        collectCallArgs(child, out);
}

string handleFuncCall(Node *node, const string &funcName, Node *paramsNode)
{
    if (has_semantic_error)
        return "error";
    Symbol *sym = ctx.lookup(funcName);
    if (!sym)
    {
        reportError(3, node->line, "undefined function \"" + funcName + "\".");
        return "error";
    }
    if (sym->kind != "func")
    {
        reportError(5, node->line, "\"" + funcName + "\" is not a function.");
        return "error";
    }
    vector<Node *> argNodes;
    if (paramsNode)
    {
        collectCallArgs(paramsNode, argNodes);
    }
    else
    {
        // 如果没有paramsNode，从FuncCall节点的子节点中查找FuncRParams
        for (auto c : node->child)
        {
            if (c && c->name.find("FuncR") != string::npos)
            {
                collectCallArgs(c, argNodes);
                break;
            }
        }
    }
    vector<string> argTypes;
    for (auto arg : argNodes)
        argTypes.push_back(checkExp(arg));
    bool paramError = false;
    if (static_cast<int>(argTypes.size()) != sym->paramCount)
    {
        reportError(9, node->line, "function \"" + funcName 
            + "\" expects " + to_string(sym->paramCount) 
            + " arguments but " + to_string(argTypes.size()) + " given.");
        paramError = true;
    }
    else
    {
        for (size_t i = 0; i < argTypes.size(); ++i)
        {
            if (argTypes[i] == "error")
                continue;
            if (i >= sym->paramTypes.size() || argTypes[i] != sym->paramTypes[i])
            {
                reportError(9, node->line, "argument " + to_string(i + 1) + " of function \"" + funcName + "\" mismatched.");
                paramError = true;
                break;
            }
        }
    }
    return paramError ? "error" : sym->type;
}

bool isFuncCallNode(Node *node, string &funcName, Node *&paramsNode)
{
    if (!node)
        return false;
    auto hasParen = [&]()
    {
        for (auto c : node->child)
        {
            if (c && (c->name == "LPAREN" || c->name == "RPAREN"))
                return true;
        }
        return false;
    };

    if (node->name == "FuncCall" && !node->child.empty() && node->child[0])
    {
        funcName = node->child[0]->attr;
        paramsNode = nullptr;
        for (size_t i = 1; i < node->child.size(); ++i)
        {
            Node *cand = node->child[i];
            if (cand && cand->name.find("FuncR") != string::npos)
            {
                paramsNode = cand;
                break;
            }
        }
        return true;
    }

    if ((node->name == "UnaryExp" || node->name == "PrimaryExp") &&
        !node->child.empty() && node->child[0] && node->child[0]->name == "Ident" &&
        hasParen())
    {
        funcName = node->child[0]->attr;
        paramsNode = nullptr;
        for (auto c : node->child)
        {
            if (c && c->name.find("FuncR") != string::npos)
            {
                paramsNode = c;
                break;
            }
        }
        return true;
    }
    return false;
}

void checkVarDef(Node *node, string typeName)
{
    // VarDef -> Ident ...
    Node *ident = node->child[0];
    string name = ident->attr;
    int line = ident->line;

    Symbol sym;
    sym.name = name;
    sym.type = typeName;
    sym.kind = "var";
    sym.definedLine = line;

    // 检查数组定义 (VarDef -> Ident ArrayDims)
    for (auto c : node->child)
    {
        if (c && c->name == "ArrayDims")
        {
            sym.isArray = true;
            sym.kind = "array";
        }
    }

    if (!ctx.define(sym))
    {
        reportError(2, line, "redefined variable \"" + name + "\".");
    }

    // 初始化检查
    for (size_t i = 0; i < node->child.size(); ++i)
    {
        if (!node->child[i])
            continue;
        if (node->child[i]->name == "ASSIGN" && i + 1 < node->child.size())
        {
            Node *init = node->child[i + 1];
            if (init && !init->child.empty())
            {
                string expType = checkExp(init->child[0]);
                if (expType != "error" && expType != "void" && expType != typeName)
                {
                    reportError(11, line, "Type mismatched for initialization.");
                }
            }
        }
    }
}

void checkFuncDef(Node *node)
{
    // FuncDef -> FuncType Ident [FuncFParams] Block
    string retType = node->child[0]->child[0]->attr;
    string name = node->child[1]->attr;
    int line = node->child[1]->line;

    Symbol funcSym;
    funcSym.name = name;
    funcSym.kind = "func";
    funcSym.type = retType;
    funcSym.definedLine = line;

    vector<string> paramTypes;
    Node *paramsNode = nullptr;
    for (auto c : node->child)
    {
        if (c && c->name == "FuncFParams")
        {
            paramsNode = c;
            break;
        }
    }
    if (paramsNode)
    {
        for (auto param : paramsNode->child)
        {
            if (!param || param->child.size() < 2)
                continue;
            string pType = param->child[0]->child[0]->attr;
            paramTypes.push_back(pType);
        }
    }
    funcSym.paramCount = static_cast<int>(paramTypes.size());
    funcSym.paramTypes = paramTypes;

    if (!ctx.define(funcSym))
    {
        reportError(4, line, "redefined function \"" + name + "\".");
    }

    ctx.enterScope();
    ctx.currentFuncReturnType = retType;

    if (paramsNode)
    {
        size_t idx = 0;
        for (auto param : paramsNode->child)
        {
            if (!param || param->child.size() < 2)
                continue;
            string pType = paramTypes[idx++];
            string pName = param->child[1]->attr;
            Symbol pSym;
            pSym.name = pName;
            pSym.type = pType;
            pSym.kind = "var";
            pSym.definedLine = param->line;
            if (!ctx.define(pSym))
                reportError(2, param->line, "redefined argument \"" + pName + "\".");
        }
    }

    extern void visitNode(Node *);
    Node *block = node->child.back();
    visitNode(block);

    ctx.exitScope();
    ctx.currentFuncReturnType = "";
}

string checkExp(Node *node)
{
    if (!node)
        return "void";

    if (node->name == "Number")
    {
        if (node->child[0]->name == "FLOATCON" || node->child[0]->attr.find(".") != string::npos)
            return "float";
        return "int";
    }

    if (node->name == "LVal")
    {
        string name = node->child[0]->attr;
        Symbol *sym = ctx.lookup(name);
        if (!sym)
        {
            reportError(1, node->line, "undefined variable \"" + name + "\".");
            return "error";
        }
        if (sym->kind == "func")
        {
            reportError(6, node->line, "misused function \"" + name + "\" as variable.");
            return "error";
        }

        bool hasIndex = false;
        for (auto c : node->child)
        {
            if (c && c->name == "Index")
            {
                hasIndex = true;
                string idxType = checkExp(c->child[0]);
                if (idxType != "int" && idxType != "error")
                {
                    reportError(7, c->line, "array index is not an integer.");
                }
            }
        }
        if (hasIndex && !sym->isArray)
        {
            reportError(8, node->line, "Not an array: \"" + name + "\".");
            return "error";
        }
        if (sym->isArray)
        {
            return hasIndex ? sym->type : "array";
        }
        return sym->type;
    }

    string funcName;
    Node *paramsNode = nullptr;
    if (isFuncCallNode(node, funcName, paramsNode))
    {
        // 如果paramsNode没有被设置，尝试从node的子节点中查找
        if (!paramsNode && node->name == "FuncCall")
        {
            for (auto c : node->child)
            {
                if (c && c->name.find("FuncR") != string::npos)
                {
                    paramsNode = c;
                    break;
                }
            }
        }
        return handleFuncCall(node, funcName, paramsNode);
    }

    // 递归检查子节点，先检查是否是函数调用
    string type = "";
    for (auto c : node->child)
    {
        if (!c)
            continue;
        // 跳过标识符、常量和操作符节点
        if (c->name == "Ident" || c->name == "INTCON" || c->name.find("Op") != string::npos)
            continue;
        // 递归检查子表达式，可能会发现函数调用
        string t = checkExp(c);
        if (t == "error")
            return "error";
        if (type == "")
            type = t;
        else if (type != t && t != "void")
        {
            reportError(11, node->line, "Type mismatched for operands.");
            return "error";
        }
    }
    return type == "" ? "void" : type;
}

void visitNode(Node *node)
{
    if (!node)
        return;

    if (node->name == "CompUnit")
    {
        for (auto c : node->child)
            visitNode(c);
        Symbol *mainSym = ctx.lookup("main");
        (void)mainSym; // 若需报告缺失 main，可在此添加
        return;
    }

    if (node->name == "FuncDef")
    {
        checkFuncDef(node);
        return;
    }

    if (node->name == "Block")
    {
        ctx.enterScope();
        for (auto c : node->child)
            visitNode(c);
        ctx.exitScope();
        return;
    }

    if (node->name == "VarDecl")
    {
        string typeName = node->child[0]->child[0]->attr;
        for (size_t i = 1; i < node->child.size(); ++i)
        {
            checkVarDef(node->child[i], typeName);
        }
        return;
    }

    if (node->name == "Stmt")
    {
        bool hasReturn = false;
        for (auto c : node->child)
        {
            if (c && c->name == "Return")
            {
                hasReturn = true;
                string retType = c->child.empty() ? "void" : checkExp(c->child[0]);
                string expected = ctx.currentFuncReturnType.empty() ? "void" : ctx.currentFuncReturnType;
                if (expected == "void")
                {
                    if (retType != "void" && retType != "error")
                    {
                        reportError(10, c->line, "return type mismatch.");
                    }
                }
                else if (retType == "void" || (retType != "error" && retType != expected))
                {
                    reportError(10, c->line, "return type mismatch.");
                }
            }
        }
        if (!hasReturn)
        {
            bool isAssign = node->child.size() >= 3 && node->child[0] && node->child[0]->name == "LVal" && node->child[1] && node->child[1]->name == "ASSIGN";
            if (isAssign)
            {
                string lhsType = checkExp(node->child[0]);
                string rhsType = checkExp(node->child[2]);
                if (lhsType != "error" && rhsType != "error" && lhsType != rhsType)
                {
                    reportError(11, node->line, "Type mismatched for assignment.");
                }
            }
            else
            {
                // 检查所有子节点，对表达式节点调用checkExp
                for (auto c : node->child)
                {
                    if (!c)
                        continue;
                    // 跳过已知的非表达式节点
                    if (c->name == "Return" || c->name == "ASSIGN" || c->name == "Block" || 
                        c->name == "IfStmt" || c->name == "WhileStmt" || c->name == "BreakStmt" || 
                        c->name == "ContinueStmt")
                        continue;
                    // 对可能是表达式的节点调用checkExp
                    // 这包括Exp及其所有子类型（LOrExp, LAndExp等）
                    if (c->name.find("Exp") != string::npos || c->name == "LVal" || 
                        c->name == "Number" || c->name == "FuncCall" || c->name == "UnaryExp" ||
                        c->name == "PrimaryExp")
                    {
                        checkExp(c);
                    }
                }
            }
        }
    }

    if (node->name == "IfStmt")
    {
        if (!node->child.empty() && node->child[0])
            checkExp(node->child[0]);
        for (size_t i = 1; i < node->child.size(); ++i)
            visitNode(node->child[i]);
        return;
    }

    if (node->name == "WhileStmt")
    {
        if (!node->child.empty() && node->child[0])
            checkExp(node->child[0]);
        ctx.loopDepth++;
        for (size_t i = 1; i < node->child.size(); ++i)
            visitNode(node->child[i]);
        ctx.loopDepth--;
        return;
    }

    if (node->name == "BreakStmt")
    {
        if (ctx.loopDepth <= 0)
            reportError(12, node->line, "break statement outside of loop.");
        return;
    }

    if (node->name == "ContinueStmt")
    {
        if (ctx.loopDepth <= 0)
            reportError(13, node->line, "continue statement outside of loop.");
        return;
    }

    for (auto c : node->child)
        visitNode(c);
}

void semantic_analysis(Node *root)
{
    if (!root)
        return;
    visitNode(root);
}