
#ifndef BAY_RANDOM_H
#define BAY_RANDOM_H

/**
 * @file BayRandom.h
 *
 * @brief Bay Random Generate With 32bit State.
 *
 */

#include <stdint.h>
#include <inttypes.h>

#define BAY_SH0 1
#define BAY_SH1 10
#define BAY_SH8 8
#define BAY_MASK 0x7FFFFFFF

namespace bays4 {
    class BayRandom {
    protected:
        unsigned int status[4];
        unsigned int mat1;
        unsigned int mat2;
        unsigned int tmat;
        
        void init();
        void inline next_state();
    public:
        BayRandom();
        
        void seed(const char* seeds);
        unsigned int generate(unsigned int max);
    };
}

#endif
