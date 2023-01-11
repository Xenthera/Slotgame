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
    std::vector<double> MultList; //creating this so we don't have to regenerate it every time we need a list of mults from symbols.
    SymbolFactory();
    int GetWeightedSymbol();
    int GetSymbolIDFromMult(double multiplier);
};


#endif //CPPSANDBOX_SYMBOLFACTORY_H
