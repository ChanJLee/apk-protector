
#include "Bays4.h"

namespace bays4 {
    
    bool Base64::checkVersion(const std::string s) {
        int _wi = getIdx(s[0]) * 32 + getIdx(s[1]);
        int _x = getIdx(s[2]);
        int _check = getIdx(s[3]);
        
        return _NOW_VERSION_ >= (_wi * _x + _check) % 32;
    }
    
    std::string Base64::d(const std::string encoded_string) {
        if (!checkVersion(encoded_string)) {
            return "";
        }
        
        CodeTree tree(encoded_string.substr(0, 4).c_str());
        std::string raw_encode = tree.decode(encoded_string);
        
        int in_len = raw_encode.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;
        
        while (in_len-- && (raw_encode[in_] != '=')) {
            char_array_4[i++] = raw_encode[in_]; in_++;
            if (i ==4) {
                for (i = 0; i <4; i++)
                    char_array_4[i] = _B64_.find(char_array_4[i]);
                
                char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];
                
                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }
        
        if (i) {
            for (j = 0; j < i; j++)
                char_array_4[j] = _B64_.find(char_array_4[j]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            
            for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
        }
        
        return ret;
    }
}

