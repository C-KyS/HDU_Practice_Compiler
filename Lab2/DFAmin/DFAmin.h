// DFAmin.h
#ifndef __DFAMIN_H  // 防止重复定义
#define __DFAMIN_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include "../nfa2dfa/nfa2dfa.h"
using namespace std;

class MinDFA {
public:
    // 原始DFA的引用
    DFA* originalDFA;
    
    // 最小化DFA的状态
    set<char> minStates;                    // 最小化后的状态集合
    set<char> minStartStates;               // 最小化后的起始状态
    set<char> minAcceptStates;              // 最小化后的接受状态
    map<char, vector<pair<char, char>>> minTransitions; // 最小化后的转换边
    map<char, char> stateToPartition;        // 状态到划分的映射
    vector<set<char>> partitions;           // 划分集合
    
    int minStateNum;                        // 最小化后的状态数
    
    MinDFA(DFA* dfa);
    
    // DFA最小化主函数
    void minimize();
    
    // 获取状态在某个字符下的转移目标
    char getTransition(char state, char symbol);
    
    // 查找状态所在的划分索引
    int findPartition(char state);
    
    // 细化划分
    bool refinePartitions();
    
    // 构建最小化DFA的转换表
    void buildMinDFA();
    
    // 显示最小化DFA信息
    void showMinDFA();
    
    // 生成最小化DFA的Graphviz DOT文件
    void generateDot(const string& filename);
    
    // 检查字符串是否被最小化DFA接受
    bool isValid(string input);
};

MinDFA::MinDFA(DFA* dfa) {
    originalDFA = dfa;
    minStateNum = 0;
}

// 获取状态在某个字符下的转移目标
char MinDFA::getTransition(char state, char symbol) {
    if (originalDFA->newEdge.find(state) != originalDFA->newEdge.end()) {
        for (auto& transition : originalDFA->newEdge[state]) {
            if (transition.second == symbol) {
                return transition.first;
            }
        }
    }
    return '\0'; // 没有转移，返回空字符
}

// 查找状态所在的划分索引
int MinDFA::findPartition(char state) {
    for (size_t i = 0; i < partitions.size(); i++) {
        if (partitions[i].count(state) > 0) {
            return i;
        }
    }
    return -1;
}

// DFA最小化主函数
void MinDFA::minimize() {
    // 初始化：将所有状态分为接受状态和非接受状态两个划分
    set<char> acceptPartition;
    set<char> nonAcceptPartition;
    
    // 获取所有DFA状态
    set<char> allStates;
    for (auto& [state, transitions] : originalDFA->newEdge) {
        allStates.insert(state);
    }
    // 也要包含那些只作为目标状态的状态
    for (auto& [state, transitions] : originalDFA->newEdge) {
        for (auto& [to, symbol] : transitions) {
            allStates.insert(to);
        }
    }
    
    // 将状态分为接受和非接受
    for (char state : allStates) {
        if (originalDFA->acceptStates.count(state) > 0) {
            acceptPartition.insert(state);
        } else {
            nonAcceptPartition.insert(state);
        }
    }
    
    // 初始化划分集合
    partitions.clear();
    if (!acceptPartition.empty()) {
        partitions.push_back(acceptPartition);
    }
    if (!nonAcceptPartition.empty()) {
        partitions.push_back(nonAcceptPartition);
    }
    
    // 如果只有一个划分，说明所有状态都是接受状态或都不是，需要进一步处理
    if (partitions.size() == 1) {
        // 如果所有状态都是接受状态，那么它们可能不等价，需要根据转移来区分
        // 但通常这种情况很少见，我们先保持一个划分
    }
    
    // 不断细化划分，直到无法再细化
    bool changed = true;
    while (changed) {
        changed = refinePartitions();
    }
    
    // 构建最小化DFA
    buildMinDFA();
}

// 细化划分
bool MinDFA::refinePartitions() {
    bool changed = false;
    vector<set<char>> newPartitions;
    
    // 对每个划分进行细化
    for (auto& partition : partitions) {
        if (partition.size() <= 1) {
            // 如果划分只有一个状态，不需要细化
            newPartitions.push_back(partition);
            continue;
        }
        
        // 尝试根据转移函数细化划分
        map<string, set<char>> groups; // key是转移模式，value是状态集合
        
        for (char state : partition) {
            // 构建该状态的转移模式字符串
            string pattern = "";
            for (char symbol : originalDFA->LetterSet) {
                char target = getTransition(state, symbol);
                if (target == '\0') {
                    pattern += "NULL,";
                } else {
                    int targetPartition = findPartition(target);
                    pattern += to_string(targetPartition) + ",";
                }
            }
            
            groups[pattern].insert(state);
        }
        
        // 如果产生了新的分组，说明需要细化
        if (groups.size() > 1) {
            changed = true;
            for (auto& [pattern, states] : groups) {
                newPartitions.push_back(states);
            }
        } else {
            // 没有产生新分组，保持原划分
            newPartitions.push_back(partition);
        }
    }
    
    partitions = newPartitions;
    return changed;
}

// 构建最小化DFA的转换表
void MinDFA::buildMinDFA() {
    // 为每个划分分配一个新的状态标识符
    char newIndex = 'A';
    map<int, char> partitionToState;
    
    minStates.clear();
    minTransitions.clear();
    minStartStates.clear();
    minAcceptStates.clear();
    stateToPartition.clear();
    
    for (size_t i = 0; i < partitions.size(); i++) {
        char newState = newIndex++;
        partitionToState[i] = newState;
        minStates.insert(newState);
        minStateNum++;
        
        // 建立原状态到新状态的映射
        for (char oldState : partitions[i]) {
            stateToPartition[oldState] = newState;
            
            // 检查是否是起始状态
            if (originalDFA->startStates.count(oldState) > 0) {
                minStartStates.insert(newState);
            }
            
            // 检查是否是接受状态
            if (originalDFA->acceptStates.count(oldState) > 0) {
                minAcceptStates.insert(newState);
            }
        }
    }
    
    // 构建转换边
    // 对于每个划分，选择其中一个代表状态来构建转换
    for (size_t i = 0; i < partitions.size(); i++) {
        char newState = partitionToState[i];
        char representative = *partitions[i].begin(); // 选择划分中的第一个状态作为代表
        
        // 对于每个输入字符，查找转移
        for (char symbol : originalDFA->LetterSet) {
            char target = getTransition(representative, symbol);
            if (target != '\0') {
                int targetPartition = findPartition(target);
                if (targetPartition >= 0) {
                    char newTarget = partitionToState[targetPartition];
                    minTransitions[newState].push_back({newTarget, symbol});
                }
            }
        }
    }
}

// 显示最小化DFA信息
void MinDFA::showMinDFA() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "Minimized DFA Information:" << endl;
    cout << "========================================" << endl;
    cout << "Minimized DFA States: " << minStateNum << endl;
    cout << "Original DFA States: " << originalDFA->newStateNum << endl;
    cout << "Reduction: " << (originalDFA->newStateNum - minStateNum) << " states" << endl;
    cout << endl;
    
    cout << "Start States: ";
    for (auto s : minStartStates) cout << s << ' ';
    cout << endl;
    
    cout << "Accept States: ";
    for (auto s : minAcceptStates) cout << s << ' ';
    cout << endl;
    
    cout << "Transitions:" << endl;
    for (auto& [from, transitions] : minTransitions) {
        for (auto& [to, symbol] : transitions) {
            cout << from << " --" << symbol << "--> " << to << endl;
        }
    }
    
    cout << endl;
    cout << "State Mappings (Original -> Minimized):" << endl;
    map<char, set<char>> reverseMap; // 新状态 -> 原状态集合
    for (auto& [oldState, newState] : stateToPartition) {
        reverseMap[newState].insert(oldState);
    }
    for (auto& [newState, oldStates] : reverseMap) {
        cout << newState << " <- { ";
        for (char oldState : oldStates) {
            cout << oldState << " ";
        }
        cout << "}" << endl;
    }
    cout << "========================================" << endl;
}

// 生成最小化DFA的Graphviz DOT文件
void MinDFA::generateDot(const string& filename) {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }
    dotFile << "digraph MinDFA {" << endl;
    dotFile << "    rankdir=LR;" << endl;
    dotFile << "    size=\"8,5\";" << endl;

    // 添加 "start" 节点
    if (!minStartStates.empty()) {
        dotFile << "    \"start\" [shape=plaintext];" << endl;
        for (auto s : minStartStates) {
            dotFile << "    \"start\" -> \"" << s << "\";" << endl;
        }
    }

    // 处理接受状态
    for (auto s : minAcceptStates) {
        dotFile << "    \"" << s << "\" [shape=doublecircle, style=bold, color=green];" << endl;
    }

    // 处理普通状态
    for (auto s : minStates) {
        if (minStartStates.count(s) == 0 && minAcceptStates.count(s) == 0) {
            dotFile << "    \"" << s << "\" [shape=circle];" << endl;
        }
    }

    // 输出状态间的转换边
    for (auto& [from, transitions] : minTransitions) {
        for (auto& [to, symbol] : transitions) {
            dotFile << "    \"" << from << "\" -> \"" << to << "\" [label=\"" << symbol << "\"];" << endl;
        }
    }

    dotFile << "}" << endl;
    dotFile.close();

    cout << filename << " generate success!" << endl;
}

// 检查字符串是否被最小化DFA接受
bool MinDFA::isValid(string input) {
    if (minStartStates.empty()) {
        return false;
    }
    
    char currentState = *minStartStates.begin();
    
    for (char c : input) {
        bool found = false;
        if (minTransitions.find(currentState) != minTransitions.end()) {
            for (auto& transition : minTransitions[currentState]) {
                if (transition.second == c) {
                    currentState = transition.first;
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }
    
    return minAcceptStates.count(currentState) > 0;
}

#endif

