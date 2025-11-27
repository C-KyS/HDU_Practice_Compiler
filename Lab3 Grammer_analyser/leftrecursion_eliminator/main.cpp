#include "leftrecursion_eliminator.h"

int main() {
    // 定义存储文法文件名的字符串
    string filename = "cfg.txt";
    
    // 创建左递归消除器的对象
    LRE lre;
    
    // 从文件中读取CFG
    lre.readCFG(filename);
    
    // 打印读取的CFG
    lre.printCFG();
    cout << endl;
    
    lre.getnotend();
    
    // 消除左递归
    lre.LeftRecursion_Eliminator();
    
    // 打印消除一切左递归后的结果
    cout << "消除一切左递归后的结果为：" << endl;
    
    // 遍历并打印消除左递归后的CFG
    for (int i = 0; i < lre.cfg.size(); i++) {
        // 打印非终结符
        cout << lre.cfg[i].first << " -> ";
        
        // 获取当前非终结符对应的产生式集合的迭代器
        set<string>::iterator it = lre.cfg[i].second.begin();
        int cnt = 0; // 用于计数，以便在打印时添加分隔符'|'
        
        // 遍历产生式集合，并打印每个产生式
        for (; it != lre.cfg[i].second.end(); it++) {
            cout << *it;
            cnt++;
            
            // 如果不是最后一个产生式，则添加分隔符'|'
            if (cnt != lre.cfg[i].second.size()) {
                cout << " | ";
            }
        }
        
        // 打印换行符，以便每个产生式占一行
        cout << endl;
    }
    
    return 0; // 程序正常结束
}
