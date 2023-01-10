//
// Created by Bobby Lucero on 1/8/23.
//

#ifndef CPPSANDBOX_WININFO_H
#define CPPSANDBOX_WININFO_H


#include <vector>
#include "GameSolver.h"

class WinInfo {

public:
    std::vector<int> WinningLines;
    double BoardValue;

public:
    WinInfo(int* board, WinLines winLines, const SymbolFactory* symbolFactory);
};


#endif //CPPSANDBOX_WININFO_H
