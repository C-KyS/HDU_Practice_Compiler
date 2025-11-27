#include "nfa2dfa.h"

int main() 
{
    // 创建NFA类的实例
    NFA nfa;
    // 从指定路径的文件中读取正则表达式（文件位于上级目录的re2nfa文件夹下，文件名为re.txt）
    nfa.readfile("../re2nfa/re.txt");
    // 插入接触点（为后续的转换做准备，具体实现依赖于NFA类的内部逻辑）
    nfa.insertContact();
    // 将正则表达式转换为后缀表达式
    nfa.re2Pe();
    // 将后缀表达式转换为NFA
    nfa.pe2NFA();
    // 打印NFA的状态和转换规则（用于调试或展示）
    nfa.printNFA();
    // 生成描述NFA的DOT文件，可以用于图形化展示NFA的结构
    nfa.generateDot("nfa.dot");

    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------


    // 使用NFA实例作为参数创建DFA类的实例
    DFA dfa(nfa);
    // 对DFA进行确定性化处理（从起始状态开始）
    dfa.deterDFA(dfa.StartState);
    // 打印DFA的状态和转换规则（用于调试或展示）
    dfa.showDFA();
    // 生成描述DFA的DOT文件，可以用于图形化展示DFA的结构
    dfa.generateDot("dfa.dot");

    cout << endl;
    // 定义一个测试字符串
    string input = "abbccdd";
    // 验证测试字符串是否被DFA接受
    if (dfa.isValid(input)) {
        // 如果接受，则输出相应的信息
        cout << "String \"" << input << "\" is valid!" << endl;
    } else {
        // 如果不接受，则输出相应的信息
        cout << "String \"" << input << "\" is invalid!" << endl;
    }
    
    return 0; // 程序正常结束
}
