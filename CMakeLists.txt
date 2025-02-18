cmake_minimum_required(VERSION 3.29)
project(ITG_Galaxiebewegung)

set(CMAKE_CXX_STANDARD 14)

add_executable(ITG_Galaxiebewegung
        Code/SimulationCreateStartValues.cpp
        Code/SimulationBruteForce.cpp
        Code/main.cpp)
