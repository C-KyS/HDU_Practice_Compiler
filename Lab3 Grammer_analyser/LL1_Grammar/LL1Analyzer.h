#ifndef __LL1_ANALYZER_H__
#define __LL1_ANALYZER_H__

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "../First_Follow/First_Follow.h"

using namespace std;

class LL1Analyzer
{
public:
    explicit LL1Analyzer(const string &cfgPath);

    bool initialize();
    bool buildParsingTable();

    void printFirstSets() const;
    void printFollowSets() const;
    void printParsingTable() const;
    void runPredictiveParsing(const string &input) const;

private:
    string cfgPath;
    Grammar grammar;
    unique_ptr<FirstFollow> firstFollow;
    map<string, map<string, string>> parsingTable;
    bool grammarReady = false;
    bool tableReady = false;
    bool isLL1Grammar = false;

    bool loadGrammar();
    void computeFirstAndFollow();
    static string trim(const string &text);
    static string removeSpaces(const string &text);
    vector<string> splitProductions(const string &rightPart) const;
    set<string> firstOfString(const string &symbols) const;
    string stackToString(const vector<string> &stk) const;
    string inputToString(const string &input, size_t index) const;
};

LL1Analyzer::LL1Analyzer(const string &cfgPath) : cfgPath(cfgPath) {}

bool LL1Analyzer::initialize()
{
    if (!loadGrammar())
    {
        return false;
    }

    computeFirstAndFollow();
    return true;
}

bool LL1Analyzer::loadGrammar()
{
    ifstream file(cfgPath);
    if (!file.is_open())
    {
        cerr << "无法打开文法文件: " << cfgPath << endl;
        return false;
    }

    grammar.terminals.clear();
    grammar.nonTerminals.clear();
    grammar.productions.clear();
    grammar.startSymbol.clear();

    string line;
    enum Section
    {
        NONE,
        TERMINALS,
        PRODUCTIONS
    } section = NONE;

    bool startSymbolSet = false;

    while (getline(file, line))
    {
        string trimmedLine = trim(line);
        if (trimmedLine.empty())
        {
            continue;
        }

        if (trimmedLine == "# 终结符部分")
        {
            section = TERMINALS;
            continue;
        }

        if (trimmedLine == "# 产生式部分")
        {
            section = PRODUCTIONS;
            continue;
        }

        if (section == TERMINALS)
        {
            grammar.addTerminal(trimmedLine);
            continue;
        }

        if (section == PRODUCTIONS)
        {
            size_t arrowPos = trimmedLine.find("->");
            string arrowToken = "->";
            if (arrowPos == string::npos)
            {
                arrowPos = trimmedLine.find("→");
                arrowToken = "→";
            }

            if (arrowPos == string::npos)
            {
                cerr << "产生式格式错误: " << trimmedLine << endl;
                continue;
            }

            string left = removeSpaces(trim(trimmedLine.substr(0, arrowPos)));
            if (!startSymbolSet)
            {
                grammar.setStartSymbol(left);
                startSymbolSet = true;
            }

            string rightPart = trimmedLine.substr(arrowPos + arrowToken.size());
            vector<string> candidates = splitProductions(rightPart);
            for (const string &candidate : candidates)
            {
                string production = candidate.empty() ? "#" : candidate;
                grammar.addProduction(left, production);
            }
        }
    }

    grammar.addTerminal("$");
    grammar.addTerminal("#");

    grammarReady = true;
    return true;
}

void LL1Analyzer::computeFirstAndFollow()
{
    if (!grammarReady)
    {
        return;
    }

    firstFollow = make_unique<FirstFollow>(grammar);

    // 屏蔽原模块中的调试输出
    ostringstream sink;
    streambuf *oldBuf = cout.rdbuf();
    cout.rdbuf(sink.rdbuf());
    firstFollow->computeFirst();
    firstFollow->computeFollow();
    cout.rdbuf(oldBuf);
}

bool LL1Analyzer::buildParsingTable()
{
    if (!firstFollow)
    {
        return false;
    }

    parsingTable.clear();
    bool conflict = false;

    for (const auto &entry : grammar.productions)
    {
        const string &nonTerminal = entry.first;
        for (const string &production : entry.second)
        {
            set<string> firstSet = firstOfString(production);
            for (const string &terminal : firstSet)
            {
                if (terminal == "#")
                {
                    continue;
                }

                string &tableEntry = parsingTable[nonTerminal][terminal];
                if (!tableEntry.empty() && tableEntry != production)
                {
                    conflict = true;
                }
                tableEntry = production;
            }

            if (firstSet.count("#") > 0)
            {
                const auto &followSet = firstFollow->followSets[nonTerminal];
                for (const string &terminal : followSet)
                {
                    string &tableEntry = parsingTable[nonTerminal][terminal];
                    if (!tableEntry.empty() && tableEntry != production)
                    {
                        conflict = true;
                    }
                    tableEntry = production;
                }
            }
        }
    }

    tableReady = true;
    isLL1Grammar = !conflict;
    return isLL1Grammar;
}

void LL1Analyzer::printFirstSets() const
{
    if (!firstFollow)
    {
        cout << "FIRST集未计算。" << endl;
        return;
    }

    cout << "FIRST集：" << endl;
    for (const string &nonTerminal : grammar.nonTerminals)
    {
        auto iter = firstFollow->firstSets.find(nonTerminal);
        if (iter == firstFollow->firstSets.end())
        {
            continue;
        }

        cout << "FIRST(" << nonTerminal << ") = { ";
        for (const string &symbol : iter->second)
        {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
}

void LL1Analyzer::printFollowSets() const
{
    if (!firstFollow)
    {
        cout << "FOLLOW集未计算。" << endl;
        return;
    }

    cout << "FOLLOW集：" << endl;
    for (const string &nonTerminal : grammar.nonTerminals)
    {
        auto iter = firstFollow->followSets.find(nonTerminal);
        if (iter == firstFollow->followSets.end())
        {
            continue;
        }

        cout << "FOLLOW(" << nonTerminal << ") = { ";
        for (const string &symbol : iter->second)
        {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
}

void LL1Analyzer::printParsingTable() const
{
    if (!tableReady)
    {
        cout << "预测分析表尚未构建。" << endl;
        return;
    }

    cout << "预测分析表：" << endl;
    vector<string> terminals;
    for (const string &t : grammar.terminals)
    {
        if (t == "#")
        {
            continue;
        }
        terminals.push_back(t);
    }

    cout << left << setw(12) << "非终结符";
    for (const string &terminal : terminals)
    {
        cout << left << setw(12) << terminal;
    }
    cout << endl;

    for (const string &nonTerminal : grammar.nonTerminals)
    {
        cout << left << setw(12) << nonTerminal;
        for (const string &terminal : terminals)
        {
            string cell = "-";
            auto rowIt = parsingTable.find(nonTerminal);
            if (rowIt != parsingTable.end())
            {
                auto colIt = rowIt->second.find(terminal);
                if (colIt != rowIt->second.end() && !colIt->second.empty())
                {
                    cell = nonTerminal + "->" + colIt->second;
                }
            }
            cout << left << setw(12) << cell;
        }
        cout << endl;
    }
}

void LL1Analyzer::runPredictiveParsing(const string &input) const
{
    if (!tableReady)
    {
        cout << "尚未构建预测分析表，无法进行分析。" << endl;
        return;
    }

    if (!isLL1Grammar)
    {
        cout << "当前文法不是LL(1)，预测分析过程无效。" << endl;
        return;
    }

    string sanitizedInput = input;
    sanitizedInput.erase(remove_if(sanitizedInput.begin(), sanitizedInput.end(), ::isspace), sanitizedInput.end());
    sanitizedInput.push_back('$');

    vector<string> analysisStack = {"$", grammar.startSymbol};
    size_t index = 0;
    int step = 1;
    bool accepted = false;

    cout << "预测分析过程：" << endl;
    cout << left << setw(8) << "步骤"
         << setw(20) << "栈"
         << setw(20) << "输入"
         << setw(20) << "动作" << endl;

    while (!analysisStack.empty())
    {
        string stackSnapshot = stackToString(analysisStack);
        string inputSnapshot = inputToString(sanitizedInput, index);
        string top = analysisStack.back();
        string action;

        if (top == "#")
        {
            analysisStack.pop_back();
            action = "弹出ε";
        }
        else if (top == "$")
        {
            if (index < sanitizedInput.size() && sanitizedInput[index] == '$')
            {
                analysisStack.pop_back();
                action = "接受";
                accepted = true;
            }
            else
            {
                action = "错误：未读到$";
                analysisStack.pop_back();
            }
        }
        else if (grammar.terminals.count(top))
        {
            if (index < sanitizedInput.size() && top[0] == sanitizedInput[index])
            {
                analysisStack.pop_back();
                index++;
                action = "匹配 " + top;
            }
            else
            {
                action = "错误：期望 " + top;
                analysisStack.pop_back();
            }
        }
        else
        {
            string lookahead(1, index < sanitizedInput.size() ? sanitizedInput[index] : '$');
            string production;

            auto rowIt = parsingTable.find(top);
            if (rowIt != parsingTable.end())
            {
                auto colIt = rowIt->second.find(lookahead);
                if (colIt != rowIt->second.end())
                {
                    production = colIt->second;
                }
            }

            if (production.empty())
            {
                action = "错误：无产生式";
                analysisStack.clear();
            }
            else
            {
                analysisStack.pop_back();
                if (production != "#")
                {
                    for (auto it = production.rbegin(); it != production.rend(); ++it)
                    {
                        string symbol(1, *it);
                        analysisStack.push_back(symbol);
                    }
                }
                action = top + "→" + production;
            }
        }

        cout << left << setw(8) << step
             << setw(20) << stackSnapshot
             << setw(20) << inputSnapshot
             << setw(20) << action << endl;
        step++;

        if (accepted)
        {
            break;
        }

        if (action.rfind("错误", 0) == 0)
        {
            break;
        }
    }

    if (accepted)
    {
        cout << "分析成功，输入串属于该文法。" << endl;
    }
    else
    {
        cout << "分析失败，输入串不属于该文法。" << endl;
    }
}

set<string> LL1Analyzer::firstOfString(const string &symbols) const
{
    set<string> result;
    if (symbols == "#")
    {
        result.insert("#");
        return result;
    }

    bool epsilonPossible = true;
    size_t index = 0;

    while (epsilonPossible && index < symbols.size())
    {
        string symbol(1, symbols[index]);
        if (grammar.terminals.count(symbol))
        {
            result.insert(symbol);
            epsilonPossible = false;
        }
        else
        {
            auto it = firstFollow->firstSets.find(symbol);
            if (it != firstFollow->firstSets.end())
            {
                for (const string &s : it->second)
                {
                    if (s != "#")
                    {
                        result.insert(s);
                    }
                }
                epsilonPossible = it->second.count("#") > 0;
            }
            else
            {
                epsilonPossible = false;
            }
        }
        index++;
    }

    if (epsilonPossible)
    {
        result.insert("#");
    }

    return result;
}

string LL1Analyzer::stackToString(const vector<string> &stk) const
{
    string repr;
    for (const string &symbol : stk)
    {
        repr += symbol;
    }
    return repr;
}

string LL1Analyzer::inputToString(const string &input, size_t index) const
{
    if (index >= input.size())
    {
        return "$";
    }
    return input.substr(index);
}

string LL1Analyzer::trim(const string &text)
{
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos)
    {
        return "";
    }
    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

string LL1Analyzer::removeSpaces(const string &text)
{
    string cleaned;
    for (char c : text)
    {
        if (!isspace(static_cast<unsigned char>(c)))
        {
            cleaned.push_back(c);
        }
    }
    return cleaned;
}

vector<string> LL1Analyzer::splitProductions(const string &rightPart) const
{
    vector<string> parts;
    string token;
    stringstream ss(rightPart);
    while (getline(ss, token, '|'))
    {
        string cleaned = removeSpaces(trim(token));
        if (cleaned == "ε")
        {
            cleaned = "#";
        }
        parts.push_back(cleaned);
    }
    return parts;
}

#endif

