//
// Created by bobby on 1/14/23.
//

#ifndef CPPSANDBOX_CONSOLE_H
#define CPPSANDBOX_CONSOLE_H


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>


class Game;
class Console {
private:
    std::vector<std::string> tokenizeString(std::string str, char delimiter);

public:
    void RunCommand(Game* pge, const std::string& command);

};


#endif //CPPSANDBOX_CONSOLE_H
