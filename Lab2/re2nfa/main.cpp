#include "re2nfa.h"

int main()
{
    NFA nfa;                    // 创建NFA对象
    nfa.readfile("./re.txt");   // 读取正则表达式
    nfa.insertContact();        // 构造NFA
    nfa.re2Pe();                // 构造PE
    nfa.pe2NFA();               // 构造NFA
    nfa.printNFA();             // 输出NFA
    nfa.generateDot("nfa.dot"); // 生成dot文件

    string testString = "fsfesf"; // 测试字符串
    if (nfa.validateString(testString))
    {
        // 测试字符串被NFA接受
        cout << "The string \"" << testString << "\" is accepted by the NFA." << endl;
    }
    else
    {
        // 测试字符串不被NFA接受
        cout << "The string \"" << testString << "\" is NOT accepted by the NFA." << endl;
    }

    return 0;
}
