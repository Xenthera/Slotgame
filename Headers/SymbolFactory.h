//
// Created by Bobby Lucero on 1/8/23.
//

#include <iostream>
#include <vector>
#include "Symbol.h"

#ifndef CPPSANDBOX_SYMBOLFACTORY_H
#define CPPSANDBOX_SYMBOLFACTORY_H


class SymbolFactory {
public:
    std::vector<Symbol> Symbols;
    SymbolFactory();
    int GetWeightedSymbol();
};


#endif //CPPSANDBOX_SYMBOLFACTORY_H
