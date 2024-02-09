#!/bin/bash

case $1 in
    cpp)
    g++ ./src/cpp/sudoku.cpp -o build/sudoku-cpp
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


