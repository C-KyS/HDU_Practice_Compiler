#include "LL1Analyzer.h"

int main()
{
    const string cfgPath = "cfg.txt";
    LL1Analyzer analyzer(cfgPath);

    if (!analyzer.initialize())
    {
        cerr << "初始化失败，程序结束。" << endl;
        return 1;
    }

    bool isLL1 = analyzer.buildParsingTable();
    cout << "LL(1)判定结果: " << (isLL1 ? "该文法是LL(1)文法" : "该文法不是LL(1)文法") << endl;

    analyzer.printFirstSets();
    analyzer.printFollowSets();
    analyzer.printParsingTable();

    if (!isLL1)
    {
        cout << "由于文法不是LL(1)，无法继续预测分析过程。" << endl;
        return 0;
    }

    cout << "请输入待分析串（程序会自动追加$）: ";
    string input;
    cin >> input;
    analyzer.runPredictiveParsing(input);

    return 0;
}

