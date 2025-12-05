#ifndef AST_H
#define AST_H
#include <vector>
#include <string>

struct Node {
    std::string name;      // 语法单元或词法单元名
    int line = 0;          // 首单词行号，0 表示 ε 或词法单元
    std::string attr;      // 附加属性：ID 符号、TYPE:int/float、INTCON 值
    std::vector<Node*> child;
    Node(const std::string &n, int l=0, const std::string &a=""):name(n),line(l),attr(a){}
    void print(int dep=0); // 先序打印，实现放在 ss.y 末尾
};
#endif