
#include <stdlib.h>
#include "Bays4.h"

namespace bays4 {
    
    std::string Base64::genSign() {
        std::string _s = "";
        int _wi = 0;
        for (int i = 0; i < 2; ++i) {
            int idx = rand() % (sizeof(_B32_) - 1);
            _s += _B32_[idx];

            _wi *= 32;
            _wi += idx;
        }

        int _x = rand() % (sizeof(_B32_) - 1);
        _s += _B32_[_x];

        int _check = _NOW_VERSION_ - ((_x * _wi) % 32);
        if (_check < 0) {
            _check += 32;
        }

        _s += _B32_[_check];
        return _s;
    }
    
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
    
    std::string Base64::e(const std::string bytes_to_encode) {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];
        
        for (int _i = 0; _i < bytes_to_encode.length(); ++_i) {
            char_array_3[i++] = bytes_to_encode[_i];
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;
                
                for(i = 0; (i <4) ; i++)
                    ret += _B64_[char_array_4[i]];
                i = 0;
            }
        }
        
        if (i) {
            for(j = i; j < 3; j++)
                char_array_3[j] = '\0';
            
            char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            
            for (j = 0; (j < i + 1); j++)
                ret += _B64_[char_array_4[j]];
            
            while((i++ < 3))
                ret += '=';
            
        }
        
        CodeTree tree(genSign().c_str());
        return tree.encode(ret);
    }
    
}

