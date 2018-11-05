cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") 
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
project(compiler)
add_executable(${PROJECT_NAME}  1G_FA.cpp 2NFA_DFA.cpp 3DFA_CO.cpp 2-5DFA_SDFA.cpp 1.cpp)