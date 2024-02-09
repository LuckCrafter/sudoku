#include <iostream>
/*
    A B C   D E F  G H I
  ------------------------
0|	1 2 3   4 5 6   7 8 9
1|	4 5 6   7 8 9   1 2 3
2|	7 8 9   1 2 3   4 5 a6
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

void printboard(int board[9][9]) {
	for (int y=0;y<9;y++) {
		for (int x=0;x<9;x++) {
			std::cout << board[y][x];
			std::cout << " ";
			if(x%3>1) {std::cout << "  ";}
		}
		std::cout << "\n";
		if(y%3>1) {std::cout << "\n";}

	}
}
void printnote(bool boards[9][9][9]) {
	for (int board=0;board<9;board++) {
		for (int y=0;y<9;y++) {
			for (int x=0;x<9;x++) {
				if (!boards[board][y][x]) {
					std::cout << board+1;
				} else {
					std::cout << 0;
				}
				std::cout << " ";
				if(x%3>1) {std::cout << "  ";}
			}
			std::cout << "\n";
			if(y%3>1) {std::cout << "\n";}
		}
		std::cout << "\n";
	}
}

int main() {
	int feld[9][9] = {
	{5,3,0,0,7,0,0,0,0},
	{6,0,0,1,9,5,0,0,0},
	{0,9,8,0,0,0,0,6,0},
	{8,0,0,0,6,0,0,0,3},
	{4,0,0,8,0,3,0,0,1},
	{7,0,0,0,2,0,0,0,6},
	{0,6,0,0,0,0,2,8,0},
	{0,0,0,4,1,9,0,0,5},
	{0,0,0,0,8,0,0,7,0}
	};

	bool note[9][9][9] {false};
	for (int y=0;y<9;y++) {
		for (int x=0;x<9;x++) {
			if(feld[y][x]) {
				int board = feld[y][x]-1;
				for (int i=0;i<9;i++) {
					note[board][y][i] = true; // remove horizontal
					note[board][i][x] = true; // remove verticale
					note[board][(y/3)*3+i%3][(x/3)*3+i/3] = true; // remove 3x3 cube
				}
			}
		}
	}

	int feld2[9][9] {};
	for (int i=0;i<81;i++) {
		for (int j=0;j<9;j++) {
			if (note[j][i/9][i%9]) {
				feld2[i/9][i%9]++;
			}
		}
	}
/*
	int feld3[9][9] {};
	for (int i=0;i<81;i++) {
		for (int j=0;j<9;j++) {
			if ()
*/

	printnote(note);
	return 0;
}