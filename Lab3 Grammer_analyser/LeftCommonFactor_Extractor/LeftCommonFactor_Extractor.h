#ifndef __LEFTCOMMONFACTOR_EXTRACTOR_H
#define __LEFTCOMMONFACTOR_EXTRACTOR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Trie 树节点类
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;  // 子节点，字符为键，节点为值
    bool isEndOfWord;  // 标记是否为候选式的结尾
    vector<string> remainingStrings;  // 存储该节点对应的候选式的后缀部分

    TrieNode() : isEndOfWord(false) {}
};

// Trie 树类
class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // 插入候选式到Trie树中
    void insert(const string& candidate) {
        TrieNode* node = root;
        for (size_t i = 0; i < candidate.size(); ++i) {
            char c = candidate[i];
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->remainingStrings.push_back(candidate.substr(i + 1)); // 存储后缀
        }
        node->isEndOfWord = true;
    }

    // 查找并提取所有可能的公共前缀
    vector<string> findAllCommonPrefixes() {
        vector<string> prefixes;
        findAllCommonPrefixesHelper(root, "", prefixes);
        return prefixes;
    }

    // 获取该节点的所有后缀部分
    vector<string> getRemainingStrings() {
        vector<string> suffixes;
        getRemainingStringsHelper(root, suffixes);
        return suffixes;
    }

private:
    void getRemainingStringsHelper(TrieNode* node, vector<string>& suffixes) {
        if (node->isEndOfWord) {
            suffixes.insert(suffixes.end(), node->remainingStrings.begin(), node->remainingStrings.end());
        }
        for (auto& child : node->children) {
            getRemainingStringsHelper(child.second, suffixes);
        }
    }

    void findAllCommonPrefixesHelper(TrieNode* node, string currentPrefix, vector<string>& prefixes) {
    if (node->children.size() > 1) {
        // 只有当节点有多个子节点时，才将当前前缀视为公共前缀
        if (!currentPrefix.empty()) {
            prefixes.push_back(currentPrefix);
        }
    }

    for (auto& child : node->children) {
        findAllCommonPrefixesHelper(child.second, currentPrefix + child.first, prefixes);
    }
}
};

// 文法类
class Grammar {
public:
    unordered_map<string, vector<string>> productions;

    // 添加产生式
    void addProduction(const string& nonTerminal, const vector<string>& rules) {
        productions[nonTerminal] = rules;
    }

    // 从文件中读取产生式并加载到 Grammar 对象
    void loadGrammarFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        unordered_map<string, vector<string>> tempProductions;
        string line;
        while (getline(infile, line)) {
            if (line.empty()) continue; // 跳过空行

            // 使用 "->" 分隔产生式左部和右部
            size_t arrowPos = line.find("->");
            if (arrowPos == string::npos) {
                cerr << "Error: Invalid format in line: " << line << endl;
                continue;
            }

            string nonTerminal = line.substr(0, arrowPos);
            nonTerminal.erase(remove(nonTerminal.begin(), nonTerminal.end(), ' '), nonTerminal.end()); // 去掉空格

            string rightPart = line.substr(arrowPos + 2);
            stringstream ss(rightPart);
            string rule;
            while (getline(ss, rule, '|')) {
                rule.erase(remove(rule.begin(), rule.end(), ' '), rule.end()); // 去掉空格
                tempProductions[nonTerminal].push_back(rule);
            }
        }

        infile.close();

        // 将解析的产生式添加到 Grammar 对象
        for (const auto& production : tempProductions) {
            addProduction(production.first, production.second);
        }
    }

    // 输出去除左公共因子的文法
    void printGrammar() {
        for (const auto& production : productions) {
            cout << production.first << " -> ";
            for (size_t i = 0; i < production.second.size(); ++i) {
                cout << production.second[i];
                if (i != production.second.size() - 1) {
                    cout << " | ";
                }
            }
            cout << endl;
        }
    }

    // 提取左公共因子并生成等价文法
    void removeLeftFactoring() {
        unordered_map<string, vector<string>> newProductions;

        for (auto& prod : productions) {
            vector<string> candidates = prod.second;
            string nonTerminal = prod.first;
            int suffixIndex = 1; // 用于生成不同的非终结符

            Trie trie;
            for (const string& candidate : candidates) {
                trie.insert(candidate);
            }

            vector<string> prefixes = trie.findAllCommonPrefixes();

            for (const string& prefix : prefixes) {
                string newNonTerminal = nonTerminal + to_string(suffixIndex++);
                vector<string> newRules;
                vector<string> remainingRules;

                for (const string& candidate : candidates) {
                    if (candidate.find(prefix) == 0) {
                        string suffix = candidate.substr(prefix.size());
                        if (suffix.empty()) {
                            newRules.push_back(""); // 如果没有后缀，添加空字符串
                        } else {
                            newRules.push_back(suffix);
                        }
                    } else {
                        remainingRules.push_back(candidate);
                    }
                }

                newProductions[nonTerminal].push_back(prefix + newNonTerminal);
                newProductions[newNonTerminal] = newRules;
                candidates = remainingRules;
            }

            if (!candidates.empty()) {
                newProductions[nonTerminal].insert(newProductions[nonTerminal].end(), candidates.begin(), candidates.end());
            }
        }

        productions = newProductions;
    }

};



#endif

