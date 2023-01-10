//
// Created by Bobby Lucero on 1/8/23.
//

#ifndef CPPSANDBOX_MATH_H
#define CPPSANDBOX_MATH_H

#include <cstdlib>
#include <ctime>

class Math{

public:
    static void setSeed(int seed){
        srand(seed);
    }
    /*
     * Max Inclusive
     */
    static int random(int min, int max) //range : [min, max]
    {
        return min + rand() % (( max + 1 ) - min);
    }
};
#endif //CPPSANDBOX_MATH_H
