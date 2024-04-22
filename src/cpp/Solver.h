#include <array>
#include "Board.h"
#include <iostream>
#include "Print.h"
using IntArray = std::array<std::array<std::array<int, 4>, 9>, 9>;

bool finalBoard(Board const& board);
bool validBoard(Board const& board);
//Board generateNotes(Board);
IntArray schritt2(Board const& board);
Board schritt3(IntArray,Board& board);
Board smartSolving(Board const& board);
Board smartbruteforce(Board const& board);
Board dumpbruteforce(Board const& board);
Board bruteforce(Board const&, bool);
