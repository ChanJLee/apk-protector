
#include "CodeTree.h"

namespace bays4 {
    
    CodeTree::CodeTree(const char* sign) {
        this->init(sign);
    }
    
    void CodeTree::init(const char * sign) {
        this->random.seed(sign);
        this->sign = std::string(sign);
        
        for (int i = 0; i < 64; ++i) {
            this->addSymbol(_B64_CODE_[i], _CNT_[(i + 1) / 11]);
        }
        this->_inter['='] = "=";
    }
    
    CodeTree::~CodeTree() {
        for (auto node_ptr : nodes) {
            // std::cerr << "do delete node\n";
            delete node_ptr;
        }
        //this->_inter.clear();
        this->_inter.erase(this->_inter.begin(), this->_inter.end());
        //delete *(this->_inter);
    }
    
    std::string CodeTree::addSymbol(const char c, int l) {
        Node* ptr = &this->head;
        std::string symbol = "";
        
        for (int i = 0; i < l; ++i) {
            char _;
            for (_ = _B32_CODE_[this->random.generate(32)];
                 ptr->children.find(_) != ptr->children.end() && ptr->children[_]->ch != '.';
                 _ = _B32_CODE_[this->random.generate(32)]) {}
            
            symbol += _;
            if (ptr->children.find(_) == ptr->children.end()) {
                ptr->children[_] = new Node();
                this->nodes.push_back(ptr->children[_]);
            }
            
            ptr = ptr->children[_];
        }
        ptr->ch = c;
        
        this->_inter[c] = symbol;
        return symbol;
    }
    
    std::string CodeTree::encode(const std::string ori) {
        std::string enc = this->sign;
        for (int i = 0; ori[i] != '\0'; ++i) {
            enc += this->_inter[ori[i]];
        }
        return enc;
    }
    
    std::string CodeTree::decode(const std::string enc) {
        std::string dec = "";
        
        for (int i = 4; enc[i] != '\0';) {
            if (enc[i] == '=') {
                dec += '=';
                i++;
                continue;
            }
            Node* ptr = &this->head;
            while (ptr->children.find(enc[i]) != ptr->children.end()) {
                ptr = ptr->children[enc[i]];
                i++;
            }
            dec += ptr->ch;
        }
        
        return dec;
    }
    
}
