#ifndef __RE2NFA_H // 防止重复包含
#define __RE2NFA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <fstream>
#include <set>
using namespace std;

// NFA类定义
class NFA
{
public:
    string re;                             // 正则表达式, 例: a(b|c|d)*
    string re_;                            // 带连接符的正则表达式,
    string pe;                             // 正则表达式的后缀形式
    int stateNum;                          // NFA状态数
    pair<int, int> se;                     // 起点和终点状态编号
    vector<vector<pair<int, char>>> graph; // NFA状态关系图
    int totalCharCount;                    // 存储总字符数量
    set<char> charSet;                     // 存储不重复的字符
    int TransNum;                          // 边数

    NFA();                            // 构造函数
    bool isValidRegex(string &regex); // 判断正则表达式合法性
    void readfile(string filename);   // 读取文件
    void insertContact();// 插入连接符 .
    int priority(char c);
    void re2Pe();
    int newState();
    void pe2NFA();
    void printNFA();
    void generateDot(const string &filename);
    bool validateString(const string &input);
    set<int> getClosure(set<int> states);
};

// NFA类的构造函数
NFA::NFA()
{
    re_ = pe = "";
    stateNum = 0;
    graph.push_back(vector<pair<int, char>>());
    TransNum = 0;
}

// 判断正则表达式合法性
bool NFA::isValidRegex(string &re)
{
    // 允许的字符集合：字母、|、*、( 和 )
    for (char c : re)
    {
        if (!isalpha(c) && c != '|' && c != '*' && c != '(' && c != ')')
        {
            cerr << "Error: Illegal character '" << c << "' in the regular expression." << endl;
            return false;
        }
    }

    // 判断括号是否匹配
    stack<char> brackets;
    for (char c : re)
    {
        if (c == '(')
        {
            brackets.push(c);
        }
        else if (c == ')')
        {
            if (brackets.empty() || brackets.top() != '(')
            {
                // 栈为空或栈顶不是'(', 即有多余的')'
                cerr << "Error: Mismatched parentheses in the regular expression." << endl;
                return false;
            }
            brackets.pop();
        }
    }

    // 栈中还有'(', 即没有匹配的'('
    if (!brackets.empty())
    {
        cerr << "Error: Unmatched '(' in the regular expression." << endl;
        return false;
    }

    // 判断 | 和 * 的位置是否合理
    // 字符串开头或结尾不能是 | 或 *
    if (re[0] == '|' || re[0] == '*' || re.back() == '|')
    {
        cerr << "Error: Invalid position of '|' or '*' in the regular expression." << endl;
        return false;
    }
    for (size_t i = 1; i < re.size(); ++i)
    {
        // 连续的 | 或 * 视为错误
        if (re[i] == '*' && re[i - 1] == '|')
        {
            cerr << "Error: '*' cannot immediately follow '|'." << endl;
            return false;
        }
        // 连续的 ( 或 ) 视为错误
        if (re[i] == '|' && (re[i - 1] == '(' || re[i - 1] == '|'))
        {
            cerr << "Error: '|' cannot immediately follow '(' or another '|'." << endl;
            return false;
        }
        // 连续的 * 和 ( 视为错误
        if (re[i] == '*' && re[i - 1] == '(')
        {
            cerr << "Error: '*' cannot immediately follow '('." << endl;
            return false;
        }
    }

    // 确保正则表达式整体格式正确
    if (re.empty())
    {
        cerr << "Error: Regular expression cannot be empty." << endl;
        return false;
    }

    return true; // 所有检查通过
}

// 读取文件
void NFA::readfile(string filename)
{
    ifstream fin(filename);
    string re;
    fin >> re;
    if (!isValidRegex(re))
    {
        throw invalid_argument("Invalid regular expression.");
    }
    this->re = re;
}

// 插入连接符 .
void NFA::insertContact()
{
    for (int i = 0; i < re.size() - 1; i++)
    {

        // 只添加字母到字符集
        if (isalpha(re[i]))
        {
            charSet.insert(re[i]); // charSet 存储不重复的字符
        }

        re_ += re[i];
        if (re[i] != '(' && re[i + 1] != ')' && re[i] != '|' && re[i + 1] != '|' && re[i + 1] != '*')
            re_ += '.';
    }
    re_ += re.back();
    if (isalpha(re.back()))
    {
        charSet.insert(re.back());
    }
    // 记录总字符数量
    totalCharCount = charSet.size();
}

// 运算符优先级
int NFA::priority(char c)
{
    if (c == '*')
        return 3;
    else if (c == '.')
        return 2;
    else if (c == '|')
        return 1;
    else
        return 0;
}
// 正则表达式转换为后缀形式
void NFA::re2Pe()
{
    stack<char> op;
    for (auto c : re_)
    {
        if (c == '(')
            op.push(c);
        else if (c == ')')
        {
            while (op.top() != '(')
            {
                pe += op.top();
                op.pop();
            }
            op.pop();
        }
        else if (c == '*' || c == '.' || c == '|')
        {
            while (op.size())
            {
                if (priority(c) <= priority(op.top()))
                {
                    pe += op.top();
                    op.pop();
                }
                else
                    break;
            }
            op.push(c);
        }
        else
            pe += c;
    }
    while (op.size())
    {
        pe += op.top();
        op.pop();
    }
}
// 生成新状态
int NFA::newState()
{
    graph.push_back(vector<pair<int, char>>()); // 生成新状态的边集
    return ++stateNum;
}
// 后缀转换为NFA
void NFA::pe2NFA()
{
    stack<pair<int, int>> states; // 状态栈
    int s, e;                     // 状态边起点和终点状态编号
    for (auto c : pe)
    {
        if (c != '*' && c != '.' && c != '|')
        {
            // 若c为字符，则创建一个新的NFA片段
            s = newState();
            e = newState();
            states.push(make_pair(s, e));
            graph[s].push_back(make_pair(e, c)); 
            TransNum++;
            continue;
        }
        switch (c)
        {
        case '*':
        {
            pair<int, int> origin = states.top();
            states.pop();
            s = newState();
            e = newState();
            states.push(make_pair(s, e));
            graph[s].push_back(make_pair(origin.first, '#'));
            graph[s].push_back(make_pair(e, '#'));
            graph[origin.second].push_back(make_pair(e, '#'));
            graph[origin.second].push_back(make_pair(origin.first, '#'));
            TransNum += 4;
            break;
        }
        case '.':
        {
            pair<int, int> right = states.top();
            states.pop();
            pair<int, int> left = states.top();
            states.pop();
            states.push(make_pair(left.first, right.second));
            graph[left.second].push_back(make_pair(right.first, '#'));
            TransNum++;
            break;
        }
        case '|':
        {
            pair<int, int> down = states.top();
            states.pop();
            pair<int, int> up = states.top();
            states.pop();
            s = newState();
            e = newState();
            states.push(make_pair(s, e));
            graph[s].push_back(make_pair(up.first, '#'));
            graph[s].push_back(make_pair(down.first, '#'));
            graph[up.second].push_back(make_pair(e, '#'));
            graph[down.second].push_back(make_pair(e, '#'));
            TransNum += 4;
            break;
        }
        default:
            break;
        }
    }
    se = make_pair(states.top().first, states.top().second);
}
// 输出NFA
void NFA::printNFA()
{
    cout << "re: " << re << "\n"
         // << "pe: " << pe << "\n"
         << "stateNum: " << stateNum << "\n"
         << "start: " << se.first << "\n"
         << "end: " << se.second << endl;

    //     << "totalCharCount: " << totalCharCount << endl; // 输出总字符数量
    // cout << "Character Set: ";
    // for (const auto& ch : charSet) { // 遍历字符集
    //     cout << ch << " "; // 输出每个字符
    // }
    // cout << "\n"; // 换行
    cout << "TransNum: " << TransNum << endl; // 输出边数
    for (int i = 1; i <= stateNum; i++)
    {
        for (auto edge : graph[i])
        {
            cout << i << " " << edge.second << " " << edge.first << "\n";
        }
    }
    cout << endl;
}
// 转成.dot
void NFA::generateDot(const string &filename)
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    fout << "digraph NFA {" << endl;
    fout << "    rankdir=LR;" << endl; // 从左到右布局
    fout << "    node [shape=circle];" << endl;

    // 起点状态和终点状态
    fout << "    \"start\" [shape=plaintext];" << endl;
    fout << "    \"start\" -> \"" << se.first << "\";" << endl;          // 起点
    fout << "    \"" << se.second << "\" [shape=doublecircle];" << endl; // 终点

    // 遍历图结构，输出边
    for (int i = 1; i <= stateNum; ++i)
    {
        for (auto &edge : graph[i])
        {
            char label = edge.second;
            fout << "    \"" << i << "\" -> \"" << edge.first << "\" [label=\"" << label << "\"];" << endl;
        }
    }

    fout << "}" << endl;
    fout.close();
    cout << "NFA graph written to " << filename << endl;
}

bool NFA::validateString(const string &input)
{
    // 获取起始状态的 ε-闭包
    set<int> currentStates = getClosure({se.first});

    // 遍历输入字符串
    for (char c : input)
    {
        set<int> nextStates;

        // 遍历当前所有状态，寻找符合输入字符 c 的边
        for (int state : currentStates)
        {
            for (auto &edge : graph[state])
            {
                if (edge.second == c)
                { // 如果边匹配输入字符
                    nextStates.insert(edge.first);
                }
            }
        }

        // 对新的状态集合计算 ε-闭包
        currentStates = getClosure(nextStates);

        // 如果没有有效的下一状态，说明字符串被拒绝
        if (currentStates.empty())
        {
            return false;
        }
    }

    // 检查最终状态集合是否包含接受状态
    return currentStates.find(se.second) != currentStates.end();
}

// 计算 ε-闭包
set<int> NFA::getClosure(set<int> states)
{
    stack<int> stateStack;
    set<int> closure = states;

    // 将所有初始状态压入栈
    for (int state : states)
    {
        stateStack.push(state);
    }

    // 深度优先搜索 ε 转移
    while (!stateStack.empty())
    {
        int currentState = stateStack.top();
        stateStack.pop();

        for (auto &edge : graph[currentState])
        {
            if (edge.second == '#' && closure.find(edge.first) == closure.end())
            {
                closure.insert(edge.first);
                stateStack.push(edge.first);
            }
        }
    }

    return closure;
}

#endif