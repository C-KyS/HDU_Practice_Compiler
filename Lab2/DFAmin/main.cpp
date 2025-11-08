#include "DFAmin.h"

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
    cout << "========================================" << endl;
    cout << "NFA Information:" << endl;
    cout << "========================================" << endl;
    nfa.printNFA();
    // 生成描述NFA的DOT文件，可以用于图形化展示NFA的结构
    nfa.generateDot("nfa.dot");

    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------

    // 使用NFA实例作为参数创建DFA类的实例
    DFA dfa(nfa);
    // 对DFA进行确定性化处理（从起始状态开始）
    cout << endl;
    cout << "========================================" << endl;
    cout << "NFA to DFA Conversion:" << endl;
    cout << "========================================" << endl;
    dfa.deterDFA(dfa.StartState);
    // 打印DFA的状态和转换规则（用于调试或展示）
    dfa.showDFA();
    // 生成描述DFA的DOT文件，可以用于图形化展示DFA的结构
    dfa.generateDot("dfa.dot");

    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------

    // 创建最小化DFA类的实例
    MinDFA minDFA(&dfa);
    // 对DFA进行最小化处理
    cout << endl;
    cout << "========================================" << endl;
    cout << "DFA Minimization:" << endl;
    cout << "========================================" << endl;
    minDFA.minimize();
    // 打印最小化DFA的状态和转换规则（用于调试或展示）
    minDFA.showMinDFA();
    // 生成描述最小化DFA的DOT文件，可以用于图形化展示最小化DFA的结构
    minDFA.generateDot("mindfa.dot");

    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------

    cout << endl;
    // 测试字符串验证功能
    string input = "abbccdd";
    cout << "Testing string validation:" << endl;
    cout << "Input string: \"" << input << "\"" << endl;
    
    // 验证测试字符串是否被原始DFA接受
    if (dfa.isValid(input)) {
        cout << "Original DFA: String \"" << input << "\" is valid!" << endl;
    } else {
        cout << "Original DFA: String \"" << input << "\" is invalid!" << endl;
    }
    
    // 验证测试字符串是否被最小化DFA接受
    if (minDFA.isValid(input)) {
        cout << "Minimized DFA: String \"" << input << "\" is valid!" << endl;
    } else {
        cout << "Minimized DFA: String \"" << input << "\" is invalid!" << endl;
    }
    
    return 0; // 程序正常结束
}

