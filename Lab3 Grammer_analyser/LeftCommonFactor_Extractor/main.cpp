#include "LeftCommonFactor_Extractor.h"
 
int main() {
    Grammar grammar; // ÉùÃ÷Ò»¸öGrammarÀàÐÍµÄ¶ÔÏó£¬ÓÃÓÚ´æ´¢ºÍ±íÊ¾ÎÄ·¨
 
    // ¶¨Òå´æ´¢ÎÄ·¨ÎÄ¼þÃûµÄ×Ö·û´®
    string filename = "cfg.txt";
    
    // ´ÓÎÄ¼þÖÐ¼ÓÔØÎÄ·¨
    grammar.loadGrammarFromFile(filename);
 
    // ´òÓ¡Ô­Ê¼ÎÄ·¨
    std::cout << "Original Grammar:" << std::endl;
    grammar.printGrammar(); // µ÷ÓÃGrammarÀàµÄprintGrammar·½·¨´òÓ¡µ±Ç°´æ´¢µÄÎÄ·¨
 
    // ÒÆ³ýÎÄ·¨ÖÐµÄ×ó¹«Òò×Ó
    grammar.removeLeftFactoring();
 
    // ´òÓ¡ÒÆ³ý×ó¹«Òò×ÓºóµÄÎÄ·¨
    std::cout << "\nGrammar after removing Left Factoring:" << std::endl;
    grammar.printGrammar(); // ÔÙ´Îµ÷ÓÃprintGrammar·½·¨´òÓ¡¸üÐÂºóµÄÎÄ·¨
 
    return 0; // ³ÌÐòÕý³£½áÊø
}
