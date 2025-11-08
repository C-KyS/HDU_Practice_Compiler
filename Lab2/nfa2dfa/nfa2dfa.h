// nfa2dfa.h
#ifndef __NFA2DFA_H  // 防止重复定义
#define __NFA2DFA_H

#include<cstring>
#include<iostream>
#include<fstream> 
#include<vector>
#include<set>
#include<queue>
#include<limits>
#include<map>
#include"../re2nfa/re2nfa.h"
using namespace std;

const int N = 100;

class DFA {
    public:
        // 状态标识符
        char index;
        // NFA状态数
        int StateNum;
        // 起始状态和结束状态数
        int StartNum, StopNum;
        // 转换边数和字符集大小
        int TransNum, LetterSize;
        // NFA的结束状态和开始状态
        int StopState, StartState;
        // 字符集
        set<char> LetterSet;
        // DFA的状态集
        set<pair<char, set<int>>> stateSet;
        // 待处理的状态队列
        queue<set<int>> stateQueue;
        // 当前状态集
        set<int> currentState;
        // NFA的转换边
        vector<vector<pair<int, char>>> Edge;

        int newStateNum;          // 新的DFA状态数
        map<char, vector<pair<char, char>>> newEdge; // DFA的转换边
        set<char> startStates;    // DFA的起始状态集合
        set<char> acceptStates;   // DFA的接受状态集合

        DFA(NFA nfa);
        // 添加转换边
        void add(int a, int b, char signal);
        // NFA确定化为DFA
        void deterDFA(int start);
        // 查找状态集是否存在
        int findState(set<int>);
        // 获取单个状态的ε闭包
        set<int> getClosure(int cur);
        // 获取状态集的ε闭包
        set<int> getClosure(set<int> cur);
        // 获取状态集通过某字符的闭包
        set<int> getClosure(set<int> cur, char signal);
        // 显示DFA信息
        void showDFA();
        // 检查字符串是否被DFA接受
        bool isValid(string input);
        // 生成DFA的Graphviz DOT文件
        void generateDot(const string& filename);
    protected:
};

DFA::DFA(NFA nfa) {
    // 用A开始标识状态编号
    index = 'A';
    newStateNum = 0; // 新状态数初始化为0

    StateNum = nfa.stateNum; // 状态数
    StartNum = 1;
    StartState = nfa.se.first;

    StopNum = 1;
    StopState = nfa.se.second;

    LetterSize = nfa.totalCharCount;
    LetterSet = nfa.charSet;

    Edge = nfa.graph;
}

// 添加边 a->b，通过字符 signal
void DFA::add(int a, int b, char signal) {
    Edge[a].push_back({b, signal});
}

// 查找状态集 cur 是否已存在
int DFA::findState(set<int> cur) {
    for (auto k : stateSet) {
        if (k.second == cur)
            return 1;
    }
    return -1;
}

// 获取状态集 cur 通过字符 signal 的闭包
set<int> DFA::getClosure(set<int> cur, char signal) {
    set<int> newset;
    for (set<int>::iterator it = cur.begin(); it != cur.end(); it++) {
        for (auto k : Edge[*it]) {
            if (k.second == signal) {
                newset.insert(k.first);
            }
        }
    }
    return newset;
}

// 获取状态集 cur 的ε闭包
set<int> DFA::getClosure(set<int> cur) {
    set<int> newset = cur;
    queue<int> q;
    for (set<int>::iterator it = cur.begin(); it != cur.end(); it++)
        q.push(*it);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        set<int> newele = getClosure(t);
        for (set<int>::iterator it = newele.begin(); it != newele.end(); it++) {
            q.push(*it);
            newset.insert(*it);
        }
    }
    return newset;
}

// 获取单个状态 cur 的ε闭包
set<int> DFA::getClosure(int cur) {
    set<int> newset;
    for (auto k : Edge[cur]) {
        if (k.second == '#') // '#' 表示ε
            newset.insert(k.first);
    }
    return newset;
}

// NFA确定化为DFA
void DFA::deterDFA(int start) {
    // 将起始状态加入当前状态集
    currentState.insert(start);
    // 获取起始状态的ε闭包
    currentState = getClosure(currentState);
    // 新状态编号加1
    newStateNum++;
    char curStateIndex = index; // 当前状态标识符
    // 起始状态加入状态集合并入队
    stateSet.insert({index, currentState});
    stateQueue.push(currentState);

    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << " I";
    for (const auto& it : LetterSet) {
        cout << "\t\t" << it;
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    // 循环处理队列中的状态集
    while (!stateQueue.empty()) {
        auto temp = stateQueue.front();
        for (auto k : stateSet) {
            if (k.second == temp) {
                cout << " " << k.first;
                curStateIndex = k.first;
                // 如果状态集包含结束状态，将其标记为接受状态
                if (temp.count(StopState)) {
                    acceptStates.insert(k.first);
                } else {
                    startStates.insert(k.first);
                }
            }
        }
        stateQueue.pop();

        for (const auto& it : LetterSet) {
            currentState = temp;
            // 通过字符获取闭包
            currentState = getClosure(temp, it);
            // 获取结果集的ε闭包
            currentState = getClosure(currentState);
            if (!currentState.empty()) {
                if (findState(currentState) == -1) {
                    stateSet.insert({++index, currentState});
                    stateQueue.push(currentState);
                    newStateNum++;
                }
                for (auto k : stateSet) {
                    if (k.second == currentState) {
                        cout << "\t\t" << k.first;
                        newEdge[curStateIndex].push_back({k.first, it});
                    }
                }
            } else {
                cout << "\t\t" << " ";
            }
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

void DFA::showDFA() {
    cout << endl;
    cout << "New DFA States: " << newStateNum << endl;
    cout << "Start States: ";
    for (auto s : startStates) cout << s << ' ';
    cout << endl;
    cout << "Accept States: ";
    for (auto s : acceptStates) cout << s << ' ';
    cout << endl;
    cout << "Transitions:" << endl;
    for (auto& [from, transitions] : newEdge) {
        for (auto& [to, signal] : transitions) {
            cout << from << " --" << signal << "--> " << to << endl;
        }
    }
    for (auto k : stateSet) {
        char id = k.first;
        auto state = k.second;
        cout << id << " State: ";
        for (set<int>::iterator it = state.begin(); it != state.end(); it++)
            cout << *it << ' ';
        cout << endl;
    }
}

bool DFA::isValid(string input) {
    char currentState = 'A';
    if (!startStates.empty()) {
        currentState = *startStates.begin();
    }
    for (char c : input) {
        bool found = false;
        for (auto& transition : newEdge[currentState]) {
            if (transition.second == c) {
                currentState = transition.first;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return acceptStates.count(currentState) > 0;
}

void DFA::generateDot(const string& filename) {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }
    dotFile << "digraph DFA {" << endl;
    dotFile << "    rankdir=LR;" << endl;
    dotFile << "    size=\"8,5\";" << endl;

    // 添加 "start" 节点，表示DFA的起始位置
    if (!startStates.empty()) {
        dotFile << "    \"start\" [shape=plaintext];" << endl;  // start 节点，表示起始位置
        for (auto s : startStates) {
            dotFile << "    \"start\" -> \"" << s << "\";" << endl;  // 从 start 到起始状态的箭头
        }
    }

    // 处理接受状态
    for (auto s : acceptStates) {
        dotFile << "    \"" << s << "\" [shape=doublecircle, style=bold, color=green];" << endl;  // 标记接受状态为双圆圈
    }

    // 处理终点状态（如果存在）
    if (!acceptStates.empty()) {
        // 终点状态的双圆圈标记
        for (auto s : acceptStates) {
            dotFile << "    \"" << s << "\" [shape=doublecircle, style=bold, color=green];" << endl;
        }
    }

    // 处理普通状态
    for (auto s : stateSet) {
        if (startStates.count(s.first) == 0 && acceptStates.count(s.first) == 0) {
            dotFile << "    \"" << s.first << "\" [shape=circle];" << endl;  // 普通状态标记为圆形
        }
    }

    // 输出状态间的转换边
    for (auto& [from, transitions] : newEdge) {
        for (auto& [to, symbol] : transitions) {
            dotFile << "    \"" << from << "\" -> \"" << to << "\" [label=\"" << symbol << "\"];" << endl;
        }
    }

    dotFile << "}" << endl;
    dotFile.close();

    cout  << filename << "generate success! " <<  endl;
}



#endif
