#ifndef AST_H
#define AST_H
#include <vector>
#include <string>
#include <iostream>

struct Node {
    std::string name;      // 语法/词法单元名，如 "FuncDef", "Ident", "INTCON"
    int line = 0;          // 行号
    std::string attr;      // 属性值
    std::vector<Node*> child;

    Node(const std::string &n, int l=0, const std::string &a="")
        :name(n), line(l), attr(a) {}
    
    virtual ~Node() {
        for(auto c : child) delete c;
    }

    void print(int dep=0); 
};

// 语义分析入口函数 [cite: 27, 28]
void semantic_analysis(Node* root);

#endif