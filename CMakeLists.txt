cmake_minimum_required(VERSION 3.24)
project(CPPSandbox)

set(CMAKE_CXX_STANDARD 11)

add_executable(CPPSandbox Sources/main.cpp Sources/Symbol.cpp Headers/Symbol.h Sources/SymbolFactory.cpp Headers/SymbolFactory.h Sources/GameSolver.cpp Headers/GameSolver.h Headers/Math.h Headers/HelperFunctions.h Sources/WinInfo.cpp Headers/WinInfo.h)
