
#include "BayRandom.h"

#define MIN_LOOP 8
#define PRE_LOOP 8

namespace bays4 {
    
    BayRandom::BayRandom() {}
    
    void BayRandom::seed(const char* seeds) {
        
        // make random seed.
        for (int i = 0; i < 4; ++i) {
            if (seeds[i] != '\0') {
                this->status[i] = (unsigned int) seeds[i];
            } else {
                this->status[i] = 110;
            }
        }
        
        this->mat1 = this->status[1];
        this->mat2 = this->status[2];
        this->tmat = this->status[3];
        
        this->init();
    }
    
    void BayRandom::init() {
        for (int i = 1; i < MIN_LOOP; ++i) {
            this->status[i & 3] ^= i + 1812433253 * (this->status[(i - 1) & 3] ^ (this->status[(i - 1) & 3] >> 30));
        }
        
        if ((this->status[0] & BAY_MASK) == 0 &&
            this->status[1] == 0 &&
            this->status[2] == 0 &&
            this->status[3] == 0) {
            this->status[0] = 'B';
            this->status[1] = 'A';
            this->status[2] = 'Y';
            this->status[3] = 'S';
        }
        
        for (int i = 0; i < PRE_LOOP; ++i) {
            this->next_state();
        }
    }
    
    void BayRandom::next_state() {
        unsigned int x, y;
        
        y = this->status[3];
        x = (this->status[0] & BAY_MASK) ^ this->status[1] ^ this->status[2];
        x ^= (x << BAY_SH0);
        y ^= (y >> BAY_SH0) ^ x;
        this->status[0] = this->status[1];
        this->status[1] = this->status[2];
        this->status[2] = x ^ (y << BAY_SH1);
        this->status[3] = y;
        this->status[1] ^= -((unsigned int)(y & 1)) & this->mat1;
        this->status[2] ^= -((unsigned int)(y & 1)) & this->mat2;
    }
    
    unsigned int BayRandom::generate(unsigned int max) {
        this->next_state();

        unsigned int t0, t1;
        
        t0 = this->status[3];
        t1 = this->status[0] ^ (this->status[2] >> BAY_SH8);
        t0 ^= t1;
        t0 ^= -((unsigned int)(t1 & 1)) & this->tmat;
        return t0 % max;
    }
}
