//
// Created by Bobby Lucero on 1/8/23.
//

#include <vector>

template<typename T>


#ifndef CPPSANDBOX_HELPERFUNCTIONS_H
#define CPPSANDBOX_HELPERFUNCTIONS_H
class HelperFunctions{
public:
    static bool Contains(std::vector<T> &arr, T val){
        for (int i = 0; i < arr.size(); ++i) {
            if(arr[i] == val){
                return true;
            }
        }
        return false;
    }
};
#endif //CPPSANDBOX_HELPERFUNCTIONS_H
