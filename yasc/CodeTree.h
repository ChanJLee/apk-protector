
#ifndef BAY_CODETREE_H
#define BAY_CODETREE_H

/**
 * @file CodeTree.h
 *
 * @brief Bay CodeTree
 *
 */

#include "BayRandom.h"
#include <vector>
#include <map>
#include <string>

#define getIdx(x) ((x - 'A') >= 0 ? (x - 'A') : (x - 'A' + 41))

namespace bays4 {
    
    const char _B32_CODE_[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    const char _B64_CODE_[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz"
                              "0123456789+/";
    const int _CNT_[] = {1, 2, 2, 2, 2, 2};
    
    struct Node {
        char ch = '.';
        std::map<char, Node*> children;
    };
    
    class CodeTree {
    protected:
        Node head;
        BayRandom random;
        std::map<char, std::string> _inter;
        std::string sign;
        
        // Need ease all together.
        std::vector<Node*> nodes;
    private:
        void init(const char *);
        std::string addSymbol(const char, int);
    public:
        CodeTree(const char* sign);
        ~CodeTree();
        
        std::string encode(const std::string);
        std::string decode(const std::string);
    };
}

#endif
