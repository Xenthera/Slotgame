cmake_minimum_required(VERSION 3.24)
project(CPPSandbox)

set(CMAKE_CXX_STANDARD 17)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


add_executable(CPPSandbox Sources/main.cpp Sources/Symbol.cpp Headers/Symbol.h Sources/SymbolFactory.cpp Headers/SymbolFactory.h Sources/GameSolver.cpp Headers/GameSolver.h Headers/Math.h Headers/HelperFunctions.h Sources/WinInfo.cpp Headers/WinInfo.h Headers/GameEngine/olcPixelGameEngine.h)


target_link_libraries(CPPSandbox ${PNG_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

