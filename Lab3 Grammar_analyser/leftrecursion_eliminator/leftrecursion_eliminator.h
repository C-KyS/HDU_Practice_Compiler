#ifndef __LEFTRECURSION_H
#define __LEFTRECURSION_H

#include <set>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

class LRE{
public:
    vector<pair<string,set<string>>> cfg; // 存储上下文无关文法的规则
    vector<string> notend; // 存储非终结符集合

    void readCFG(const string& filename); // 从文件读取上下文无关文法
    void printCFG(); // 打印上下文无关文法
    void getnotend(); // 提取所有的非终结符
    void LeftRecursion_Eliminator(); // 消除左递归
private:
    string myreplace(string str, string s,string t); // 替换字符串中的子串
    void erasedirect(int posi); // 消除直接左递归
    bool allend(string str); // 检查字符串是否由终结符组成
    bool startsWith(const string& source, const string& prefix) const;
};

void LRE::readCFG(const string& filename) {
        ifstream infile(filename);
        string line;

        while (getline(infile, line)) {
            // 去除 Windows 行尾符 \r
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            
            // 忽略空行或以 '#' 开头的注释行
            if (line.empty() || line[0] == '#') continue;

            // 使用字符串流处理每行规则
            stringstream ss(line);
            string nonTerminal, arrow, production;
            
            // 分割获取非终结符和箭头 "->"
            getline(ss, nonTerminal, ' '); // 获取非终结符
            getline(ss, arrow, ' ');       // 获取箭头 "->"
            
            // 去除非终结符的前后空白
            size_t start = nonTerminal.find_first_not_of(" \t\r\n");
            if (start != string::npos) {
                size_t end = nonTerminal.find_last_not_of(" \t\r\n");
                nonTerminal = nonTerminal.substr(start, end - start + 1);
            }
            
            set<string> productions;
            
            // 提取生产式
            while (getline(ss, production, '|')) {
                // 去除前后空白字符（包括空格、制表符、换行符、\r）
                size_t start = production.find_first_not_of(" \t\r\n");
                if (start != string::npos) {
                    size_t end = production.find_last_not_of(" \t\r\n");
                    production = production.substr(start, end - start + 1);
                } else {
                    production.clear();
                }
                
                if (!production.empty()) {
                    productions.insert(production);  // 将生产式加入集合
                }
            }

            // 检查非终结符是否已存在于 cfg，若存在则合并生产式
            bool found = false;
            for (auto& rule : cfg) {
                if (rule.first == nonTerminal) {
                    rule.second.insert(productions.begin(), productions.end());  // 合并生产式
                    found = true;
                    break;
                }
            }
            
            // 如果非终结符不存在，则将其加入 cfg
            if (!found) {
                cfg.push_back(make_pair(nonTerminal, productions));
            }
        }

        infile.close();
    }

void LRE::printCFG() {
        cout << "原文法表达式为: " << endl;
        for (const auto& rule : cfg) {
            cout << rule.first << " -> ";
            
            // 按顺序打印生产式
            auto it = rule.second.begin();
            while (it != rule.second.end()) {
                cout << *it;
                ++it;
                if (it != rule.second.end()) {
                    cout << " | ";  // 用 " | " 分隔多个生产式
                }
            }
            
            cout << endl;
        }
    }

void LRE::getnotend(){
    for(int i = 0; i < cfg.size(); i++){
        string nonTerminal = cfg[i].first; // 获取每条规则的非终结符
        // 如果nonTerminal不在notend中，则添加
        if (find(notend.begin(), notend.end(), nonTerminal) == notend.end()) {
            notend.push_back(nonTerminal);
        }
    }

}


void LRE::LeftRecursion_Eliminator(){
    for(int i=0;i<notend.size();i++){
        int posi=-1;
        for(int j=0;j<i;j++){
            posi=-1;
            int posj=-1;
            for(int k=0;k<cfg.size();k++){// 找到当前非终结符的位置
                if(cfg[k].first==notend[i]){
                    posi=k;
                    break;
                }
            }
            for(int k=0;k<cfg.size();k++){
                if(cfg[k].first == notend[j]){// 找到前一个非终结符的位置
                    posj=k;
                    break;
                }
            }
            if(posi==-1||posj==-1)continue; // 若未找到对应位置，跳过
            set<string>::iterator it=cfg[posi].second.begin();
            set<string>::iterator it2;
            set<string> tempset;
            for(it;it!=cfg[posi].second.end();it++){
                string tempstr=*it;
                string ss;
                if(startsWith(tempstr, notend[j])){
                    for(it2=cfg[posj].second.begin();it2!=cfg[posj].second.end();it2++){
                        ss=tempstr;
                        ss=myreplace(ss,notend[j],*it2); // 替换非终结符
                        tempset.insert(ss);
                    }
                }
            }
            vector<string> temv;
            for (it = cfg[posi].second.begin(); it != cfg[posi].second.end(); it++) {
                string str = *it;
                if (startsWith(str, notend[j]))
                    temv.push_back(str); // 记录需要替换的生产式
            }
            // 删除需要替换的生产式
            for (int x = 0; x < temv.size(); x++) {
                it = cfg[posi].second.find(temv[x]);
                if (it != cfg[posi].second.end())
                    cfg[posi].second.erase(it);
            }
            // 插入替换后的生产式
            for (it = tempset.begin(); it != tempset.end(); it++){
                cfg[posi].second.insert(*it);
            }
        }
        if(i==0){
            for(int k=0;k<cfg.size();k++){// 消除直接左递归
                if(cfg[k].first==notend[i]){
                    erasedirect(k);
                    break;
                }
            }
        }
        else{
            erasedirect(posi);
        }
    }
}

string LRE::myreplace(string str, string s,string t)
{
    // 将字符串 str 中的子串 s 替换为 t
    if (str.find(s) != -1) {
        int pos = str.find(s);
        str.replace(pos, s.size(), t);
    }
    return str;
}

void LRE::erasedirect(int posi)
{
    set<string>::iterator it = cfg[posi].second.begin();

    bool flag = false;
    for (it; it != cfg[posi].second.end(); it++) {
        string str = *it;
        if ((str.find(cfg[posi].first) == str.rfind(cfg[posi].first) && str.find(cfg[posi].first) == 0)){
            flag = true; // 检测是否存在直接左递归
            break;
        }
    }
    if (!flag) return;

    vector<string> va, vb;
    for (it = cfg[posi].second.begin(); it != cfg[posi].second.end(); it++) {
        string str = *it;
        if (str.find(cfg[posi].first) == -1) {
            vb.push_back(str); // 非递归部分
        } else {
            str.erase(0, cfg[posi].first.size());
            va.push_back(str); // 递归部分
        }
    }
    cfg[posi].second.clear();
    for (int i = 0; i < vb.size(); i++) {
        cfg[posi].second.insert(vb[i] + cfg[posi].first+"'"); // 修改非递归部分
    }

    set<string> ans;
    for (int i = 0; i < va.size(); i++) {
        ans.insert(va[i] + cfg[posi].first + "'"); // 修改递归部分
    }
    ans.insert("ε"); // 添加 ε 规则
    pair<string,set<string>> N = make_pair(cfg[posi].first + "'", ans);
    cfg.push_back(N); // 添加新规则
}

bool LRE::allend(string str)
{
    // 检查字符串是否完全由终结符组成
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            return false;
    }
    return true;
}

bool LRE::startsWith(const string& source, const string& prefix) const {
    if (prefix.empty()) return true;
    if (source.size() < prefix.size()) return false;
    return equal(prefix.begin(), prefix.end(), source.begin());
}

#endif
