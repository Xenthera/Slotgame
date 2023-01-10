//
// Created by Bobby Lucero on 1/8/23.
//

#include "../Headers/SymbolFactory.h"
#include "../Headers/Math.h"

SymbolFactory::SymbolFactory(){
    Symbols.emplace_back(0, 1, 400);
    Symbols.emplace_back(1, 2, 200);
    Symbols.emplace_back(2, 3, 150);
    Symbols.emplace_back(3, 5, 100);
    Symbols.emplace_back(4, 10, 50);
    Symbols.emplace_back(5, 20, 25);
    Symbols.emplace_back(6, 50, 12);
    Symbols.emplace_back(7, 100, 6);
}

int SymbolFactory::GetWeightedSymbol() {
    int weightSum = 0;
    for (int i = 0; i < Symbols.size(); ++i) {
        weightSum += Symbols[i].weight;
    }
    int rnd = Math::random(0, weightSum);
    for (int i = 0; i < Symbols.size(); ++i) {
        if(rnd < Symbols[i].weight)
            return i;
        rnd -= Symbols[i].weight;
    }

    return -1;
}
