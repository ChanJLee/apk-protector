
#ifndef BAY_BAYS4_H
#define BAY_BAYS4_H

/**
 * @file Bays4.h
 *
 * @brief Bay Base64.
 *
 */

#include <string>
#include "CodeTree.h"

namespace bays4 {
    
    const std::string _B64_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    const char _B32_[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    
    class Base64 {
    private:
        std::string genSign();
        const int _NOW_VERSION_ = 1;
        
        bool checkVersion(const std::string);
    public:
        std::string e(const std::string);
        std::string d(std::string const);
    };

    
}

#endif
