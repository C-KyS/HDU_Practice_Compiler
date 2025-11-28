#include "First_Follow.h"


int main() {
    Grammar grammar; // 声明一个Grammar类型的对象，用于存储文法

    // 尝试从文件"cfg.txt"中读取文法
    if (!grammar.readFromFile("cfg.txt")) {
        cerr << "无法读取配置文件" << endl; // 如果读取失败，输出错误信息
        return 1;  // 返回1表示程序异常结束
    }

    FirstFollow firstFollow(grammar); // 使用已读取的文法初始化FirstFollow对象

    // 计算FIRST集
    firstFollow.computeFirst();
    // 计算FOLLOW集
    firstFollow.computeFollow();

    // 打印FIRST集
    firstFollow.printFirstSets();
    // 打印FOLLOW集
    firstFollow.printFollowSets();

    return 0; // 程序正常结束
}
