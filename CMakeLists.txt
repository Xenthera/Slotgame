cmake_minimum_required(VERSION 3.24)
project(CPPSandbox)

set(CMAKE_CXX_STANDARD 11)

add_executable(CPPSandbox main.cpp Symbol.cpp Headers/Symbol.h SymbolFactory.cpp Headers/SymbolFactory.h GameSolver.cpp Headers/GameSolver.h Headers/Math.h Headers/HelperFunctions.h)
