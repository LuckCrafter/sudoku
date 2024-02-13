#!/bin/bash

case $1 in
    cpp)
    g++ ./src/cpp/sudoku.cpp src/cpp/Print.cpp src/cpp/IOBoard.cpp src/cpp/Solver.cpp -O0 -ggdb -Wall -Wextra -o build/sudoku-cpp
    ;;
    java)
    javac blablabla
    ;;
    py)
    ;;
    *)
    echo "unknown: $1"
    ;;
esac


