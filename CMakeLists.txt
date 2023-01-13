cmake_minimum_required(VERSION 3.25)
project(CPPSandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

find_package(PGE)


add_executable(CPPSandbox Sources/main.cpp Sources/Symbol.cpp Headers/Symbol.h Sources/SymbolFactory.cpp Headers/SymbolFactory.h Sources/GameSolver.cpp Headers/GameSolver.h Headers/Math.h Headers/HelperFunctions.h Sources/WinInfo.cpp Headers/WinInfo.h Headers/GameEngine/olcPixelGameEngine.h)


target_link_libraries(CPPSandbox PRIVATE PGE)

