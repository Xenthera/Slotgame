//
// Created by Bobby Lucero on 1/8/23.
//

#include "../Headers/WinInfo.h"

WinInfo::WinInfo(int *board, WinLines winLines, const SymbolFactory* symbolFactory) {
    this->WinningLines.clear();
    this->BoardValue = 0;
    for (int i = 0; i < winLines.lines.size(); ++i) {
        if(board[winLines.lines[i][0]] == board[winLines.lines[i][1]] && board[winLines.lines[i][0]] == board[winLines.lines[i][2]]){
            this->BoardValue += symbolFactory->Symbols[board[winLines.lines[i][0]]].multiplier;
            this->WinningLines.emplace_back(i);
        }
    }
}
