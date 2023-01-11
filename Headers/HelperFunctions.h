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
    static bool Contains(std::vector<std::vector<T>> &list, std::vector<T> &element){
        for (int i = 0; i < list.size(); ++i) {
            if(isEqual(list[i], element)){
                return true;
            }
        }
        return false;
    }
    static std::vector<std::vector<T>> split_number(T n, std::vector<T> numbers) {
        std::vector<std::vector<T>> parts;
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i; j < numbers.size(); j++) {
                for (int k = j; k < numbers.size(); k++) {
                    if (i != j && j != k && i != k && numbers[i] + numbers[j] + numbers[k] == n) {
                        std::vector<T> temp_parts = {numbers[i], numbers[j], numbers[k]};
                        if(!Contains(parts, temp_parts))
                            parts.push_back(temp_parts);
                    } else if (i != j && j != k && i != k && numbers[i] + numbers[j] == n) {
                        std::vector<T> temp_parts = {numbers[i], numbers[j]};
                        if(!Contains(parts, temp_parts))
                            parts.push_back(temp_parts);
                    }
                }
            }
        }
        return parts;
    }

    static bool isEqual(std::vector<T> &first, std::vector<T> &second)
    {
        if (first.size() != second.size()) {
            return false;
        }

        std::sort(first.begin(), first.end());
        std::sort(second.begin(), second.end());

        return first == second;
    }
};
#endif //CPPSANDBOX_HELPERFUNCTIONS_H
