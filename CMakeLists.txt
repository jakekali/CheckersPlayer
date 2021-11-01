cmake_minimum_required(VERSION 2.17)
project(CheckersPlayer)


include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ggdb -Og")


set(CMAKE_CXX_STANDARD 14)

add_executable(CheckersPlayer move.h main.cpp board.h board.cpp handler.cpp handler.h move.cpp )
