cmake_minimum_required(VERSION 3.12)
project(StackGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(StackGame main.cpp Node.cpp Node.h Game.cpp Game.h)