//#include <iostream>
//#include <array>
//#include <fstream>
#include <string>
#include "Board.h"
#include "Print.h"
#include "IOBoard.h"
#include "Solver.h"
//#include "debug.h"

/*
    A B C   D E F  G H I
  ------------------------
0|	1 2 3   4 5 6   7 8 9
1|	4 5 6   7 8 9   1 2 3
2|	7 8 9   1 2 3   4 5 6
 |
3|	 3 4   5 6 7   8 9 1
4|	5 6 7   8 9 1   2 3 4
5|	8 9 1   2 3 4   5 6 7
 |
6|	3 4 5   6 7 8   9 1 2
7|	6 7 8   9 1 2   3 4 5
8|	9 1 2   3 4 5   6 7 8
*/

// Regeln 1-9 Vertikale Reihe
// Regeln 1-9 Horizontale Reihe
// Regeln 1-9 3x3 Würfel
int main() {
    //Board board;
    Board board = importBoard("./input.txt");
	Board solvedboard = bruteforce(board,true);
	printboard(board,solvedboard);
    printnote(board,solvedboard);
    exportBoard("./output.txt", solvedboard);
	return !finalBoard(solvedboard);
}
