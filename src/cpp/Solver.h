#include <array>
#include "Board.h"

using IntArray = std::array<std::array<std::array<int, 4>, 9>, 9>;

bool finalBoard(Board);
bool validBoard(Board);
//Board generateNotes(Board);
IntArray schritt2(Board);
Board schritt3(IntArray,Board);
Board smartSolving(Board);
Board smartbruteforce(Board);
Board dumpbruteforce(Board);
Board bruteforce(Board, bool);