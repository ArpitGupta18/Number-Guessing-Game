cmake_minimum_required(VERSION 3.31)
project(NumberGuessGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(NumberGuessGame main.cpp
        test.cpp)

target_link_libraries(NumberGuessGame stdc++fs)