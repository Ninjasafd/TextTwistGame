cmake_minimum_required(VERSION 3.17)
project(Hangman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -pedantic -pedantic-errors")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(TextTwist main.cpp LetterNode.cpp LetterNode.h Letter.cpp Letter.h Timer.cpp Timer.h)
add_executable(TimerTest TimerTest.cpp Timer.cpp Timer.h)