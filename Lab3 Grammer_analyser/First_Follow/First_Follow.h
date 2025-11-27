#ifndef __FIRST_FOLLOW_H__
#define __FIRST_FOLLOW_H__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

// 文法类，用于存储终结符、非终结符和产生式
class Grammar
{
public:
    set<string> terminals;                   // 终结符集合
    set<string> nonTerminals;                // 非终结符集合
    map<string, vector<string>> productions; // 产生式集合
    string startSymbol;                      // 明确的开始符号

    void setStartSymbol(const string &symbol)
    {
        startSymbol = symbol;
        nonTerminals.insert(symbol); // 确保开始符号是非终结符
    }

    // 添加产生式
    void addProduction(string nonTerminal, string production)
    {
        productions[nonTerminal].push_back(production);
        nonTerminals.insert(nonTerminal);
    }

    // 添加终结符
    void addTerminal(string terminal)
    {
        terminals.insert(terminal);
    }

    // 读取属性
    bool readFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "无法打开文件: " << filename << endl;
            return false;
        }

        string line;
        enum Section
        {
            TERMINALS,
            PRODUCTIONS
        } section = TERMINALS;

        bool firstProduction = true; // 用于标记是否是第一条产生式

        while (getline(file, line))
        {
            string trimmedLine = trim(line);
            // 跳过空行（含仅包含空白字符的行）
            if (trimmedLine.empty())
                continue;

            // 调试输出：查看当前行内容
            cout << "读取行: " << trimmedLine << endl;

            // 切换部分
            if (trimmedLine == "# 终结符部分")
            {
                section = TERMINALS;
                continue;
            }
            else if (trimmedLine == "# 产生式部分")
            {
                section = PRODUCTIONS;
                continue;
            }

            // 根据当前部分读取数据
            if (section == TERMINALS)
            {
                addTerminal(trimmedLine);
                cout << "添加终结符: " << trimmedLine << endl; // 调试输出
            }
            else if (section == PRODUCTIONS)
            {
                const vector<string> arrowSymbols = {"->", "→"};
                size_t arrowPos = string::npos;
                size_t arrowLen = 0;

                for (const auto &symbol : arrowSymbols)
                {
                    arrowPos = trimmedLine.find(symbol);
                    if (arrowPos != string::npos)
                    {
                        arrowLen = symbol.size();
                        break;
                    }
                }

                if (arrowPos == string::npos)
                {
                    cerr << "无法识别产生式（缺少箭头）: " << trimmedLine << endl;
                    continue;
                }

                string left = trim(trimmedLine.substr(0, arrowPos));
                string rightPart = trim(trimmedLine.substr(arrowPos + arrowLen));

                if (left.empty() || rightPart.empty())
                {
                    cerr << "产生式左右部不能为空: " << trimmedLine << endl;
                    continue;
                }

                vector<string> rhsList = splitProductions(rightPart);
                if (rhsList.empty())
                {
                    cerr << "无法解析产生式右部: " << trimmedLine << endl;
                    continue;
                }

                for (const auto &right : rhsList)
                {
                    addProduction(left, right);
                    cout << "添加产生式: " << left << " -> " << right << endl; // 调试输出

                    // 如果是第一条产生式，设置开始符号
                    if (firstProduction)
                    {
                        startSymbol = left;                                // 设置开始符号为第一条产生式的左部
                        cout << "设置开始符号为: " << startSymbol << endl; // 调试输出
                        firstProduction = false;                           // 后续产生式不再是第一条
                    }
                }
            }
        }

        addTerminal("$");
        addTerminal("#");
        // 打印已经读取的终结符
        cout << "\n终结符集: ";
        for (const auto &terminal : terminals)
        {
            cout << terminal << " ";
        }
        cout << endl;

        // 打印已经读取的非终结符
        cout << "\n非终结符集: ";
        for (const auto &nonTerminal : nonTerminals)
        {
            cout << nonTerminal << " ";
        }
        cout << endl;

        // 打印已经读取的产生式
        cout << "\n产生式: " << endl;
        for (const auto &production : productions)
        {
            const string &left = production.first;
            const vector<string> &right = production.second;
            for (const auto &rhs : right)
            {
                cout << left << " -> " << rhs << endl;
            }
        }

        file.close();
        return true;
    }

    // 去除字符串两端的空格
    string trim(const string &str)
    {
        const string whitespace = " \t\r\n";
        size_t first = str.find_first_not_of(whitespace); // 找到第一个非空字符
        if (first == string::npos)
            return ""; // 如果没有非空字符，返回空字符串

        size_t last = str.find_last_not_of(whitespace); // 找到最后一个非空字符
        return str.substr(first, last - first + 1);     // 返回去除空格后的子字符串
    }

    vector<string> splitProductions(const string &rhs)
    {
        vector<string> productionsList;
        stringstream ss(rhs);
        string part;
        while (getline(ss, part, '|'))
        {
            string trimmed = trim(part);
            if (!trimmed.empty())
            {
                string cleaned;
                cleaned.reserve(trimmed.size());
                for (char ch : trimmed)
                {
                    if (!isspace(static_cast<unsigned char>(ch)))
                    {
                        cleaned.push_back(ch);
                    }
                }
                productionsList.push_back(cleaned);
            }
        }
        return productionsList;
    }
};

// FIRST集和FOLLOW集计算类
class FirstFollow
{
public:
    Grammar grammar;
    map<string, set<string>> firstSets;  // FIRST集
    map<string, set<string>> followSets; // FOLLOW集

    FirstFollow(Grammar g) : grammar(g) {}

    // 计算FIRST集
    void computeFirst()
    {
        // 初始化终结符的FIRST集
        for (const string &terminal : grammar.terminals)
        {
            firstSets[terminal].insert(terminal);
        }

        bool changed = true;

        // 反复迭代直到FIRST集不再变化
        while (changed)
        {
            changed = false;

            // 遍历所有产生式
            for (const auto &entry : grammar.productions)
            {
                string nonTerminal = entry.first;

                for (const string &production : entry.second)
                {
                    size_t i = 0;
                    bool epsilonFound = true;

                    // 对于每个产生式右边的符号进行处理
                    while (i < production.size() && epsilonFound)
                    {
                        string symbol(1, production[i]);

                        if (grammar.terminals.find(symbol) != grammar.terminals.end())
                        {
                            // 如果是终结符，直接加入FIRST集
                            if (firstSets[nonTerminal].insert(symbol).second)
                            {
                                changed = true;
                            }
                            epsilonFound = false;
                        }
                        else
                        {
                            // 如果是非终结符，合并其FIRST集（去除空串）
                            const auto &firstOfSymbol = firstSets[symbol];
                            size_t before = firstSets[nonTerminal].size();

                            for (const string &sym : firstOfSymbol)
                            {
                                if (sym != "#")
                                { // 排除空串 #
                                    firstSets[nonTerminal].insert(sym);
                                }
                            }

                            if (firstSets[nonTerminal].size() > before)
                            {
                                changed = true;
                            }

                            // 如果当前符号的FIRST集不包含空串，停止继续查看后续符号
                            if (firstOfSymbol.count("#") == 0)
                            {
                                epsilonFound = false;
                            }
                        }
                        i++;
                    }

                    // 如果生产式的右边是空串，加入空串到FIRST集
                    if (epsilonFound && firstSets[nonTerminal].insert("#").second)
                    {
                        changed = true;
                    }
                }
            }
        }
    }

    // 计算FOLLOW集
    void computeFollow()
    {
        // 对每个非终结符初始化FOLLOW集
        for (const string &nonTerminal : grammar.nonTerminals)
        {
            followSets[nonTerminal] = {};
        }

        // 将 $ 加入到明确的开始符号的 FOLLOW 集
        followSets[grammar.startSymbol].insert("$");

        bool changed = true;

        // 反复迭代直到FOLLOW集不再变化
        while (changed)
        {
            changed = false;

            // 遍历所有产生式
            for (const auto &entry : grammar.productions)
            {
                string nonTerminal = entry.first; // H

                for (const string &production : entry.second /*Lso*/)
                {
                    for (size_t i = 0; i < production.size(); i++)
                    {
                        string symbol(1, production[i]);

                        // 确保处理的是非终结符
                        if (grammar.nonTerminals.find(symbol) != grammar.nonTerminals.end())
                        {
                            size_t before = followSets[symbol].size();

                            // 处理产生式右边的符号后续
                            if (i + 1 < production.size()) //说明不是最后一个符号
                            {
                                string nextSymbol(1, production[i + 1]); // symbol的下一个符号
                                const auto &firstOfNext = firstSets[nextSymbol]; // firstofnext为nextSymbol的first集

                                // 将 FIRST(下一个符号) 中的符号（不包括空串）添加到 FOLLOW(symbol)
                                for (const string &symbolInFirst : firstOfNext)
                                {
                                    if (symbolInFirst != "#")
                                    { // 排除空串符号 #
                                        followSets[symbol].insert(symbolInFirst);
                                    }
                                }

                                if (firstOfNext.count("#") > 0)
                                {
                                    // 检查下一个符号之后的符号是否都包含空串 #, 即是否可以推出空串 #
                                    bool allEmpty = true;
                                    size_t j = i + 2;
                                    while (j < production.size())
                                    {
                                        string nextNextSymbol(1, production[j]);
                                        if (firstSets[nextNextSymbol].count("#") == 0)
                                        {
                                            allEmpty = false;
                                            break;
                                        }
                                        j++;
                                    }

                                    // 如果后续符号都能推出空串 #，则将 FOLLOW(nonTerminal) 加入 FOLLOW(symbol)
                                    if (allEmpty)
                                    {
                                        followSets[symbol].insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
                                        cout << "1" << nonTerminal << endl;
                                    }
                                }
                            }
                            else
                            {
                                // 如果右边没有符号，把 FOLLOW(nonTerminal) 加入到 FOLLOW(symbol)
                                followSets[symbol].insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
                                cout << "2" << nonTerminal << endl;
                            }

                            // 如果 FOLLOW(symbol) 发生变化，设置 changed 标志
                            if (followSets[symbol].size() > before)
                            {
                                changed = true;
                                cout << "FOLLOW(" << symbol << ") 更新：";
                                for (const auto &sym : followSets[symbol])
                                {
                                    cout << sym << " ";
                                }
                                cout << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    void printFirstSets()
    {
        cout << "FIRST集: " << endl;
        for (const auto &entry : firstSets)
        {
            // 仅打印非终结符的FIRST集
            if (grammar.nonTerminals.find(entry.first) != grammar.nonTerminals.end())
            {
                cout << entry.first << " -> { ";
                for (const string &symbol : entry.second)
                {
                    cout << symbol << " ";
                }
                cout << "}" << endl;
            }
        }
    }

    void printFollowSets()
    {
        cout << "FOLLOW集: " << endl;
        for (const auto &entry : followSets)
        {
            // FOLLOW集只与非终结符相关
            if (grammar.nonTerminals.find(entry.first) != grammar.nonTerminals.end())
            {
                cout << entry.first << " -> { ";
                for (const string &symbol : entry.second)
                {
                    cout << symbol << " ";
                }
                cout << "}" << endl;
            }
        }
    }
};

#endif
