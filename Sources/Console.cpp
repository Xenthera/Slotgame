//
// Created by bobby on 1/14/23.
//

#include "../Headers/Console.h"

std::vector<std::string> Console::tokenizeString(std::string str, char delimiter) {
    std::vector<std::string> returnVector;
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delimiter)) {
        returnVector.push_back(s);
    }

    return returnVector;
}

void Console::RunCommand(Game* pge, const std::string& command) {
    std::cout << "# Of Args: " << std::endl;

    if(command == "exit"){
        exit(0);
    }

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::cout << std::put_time(&tm, "[%H:%M:%S]: ") << command << std::endl;
}
