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
	for (int y=0;y<9;++y) {
		for (int x=0;x<9;++x) {
			std::cout << board[y][x];
			std::cout << " ";
			if(x%3>1) {std::cout << "  ";}
		}
		std::cout << "\n";
		if((y+1)%3+y/8==0) {std::cout << "\n";}
	}
}

int main() {
	int feld[9][9] = {
	{6,0,0, 0,0,0, 0,0,4},
	{0,0,9, 0,8,0, 2,0,1},
	{0,0,0, 0,0,9, 0,0,0},

	{0,5,0, 1,0,0, 6,0,2},
	{0,0,0, 0,6,0, 0,3,0},
	{0,0,2, 0,0,0, 0,4,0},

	{0,0,0, 0,0,0, 0,6,0},
	{7,0,0, 5,0,0, 0,0,0},
	{0,0,3, 0,1,0, 8,0,9},
	};
	bool note[9][9][9] {false}; // Schritt 0: Notizen erstellen und auf alle felder alle zahlen als notize setzen
	bool progress=true;
	while(progress) {
		progress=false;
		//Schritt 1: Nummern von notizen entfernen die durch gesetze felder kollidieren
		for (int y=0;y<9;++y) {
			for (int x=0;x<9;++x) {
				if(feld[y][x]!=0) {
					int b = feld[y][x]-1;
					for (int i=0;i<9;++i) {
						note[b][y][i] = true; // remove horizontal
						note[b][i][x] = true; // remove verticale
						note[b][(y/3)*3+i%3][(x/3)*3+i/3] = true; // remove 3x3 cube
						note[i][y][x] = true; // remove all notes on the feld
					}
				} else {
					progress=true;
				}
			}
		}

		// Schritt 2: Prüfen ob es nummern & felder gibt die keine alternativen haben
		int tmp[9][9][4] {};
		for (int b=0;b<9;++b) {
			for (int y=0;y<9;++y) {
				for (int x=0;x<9;++x) {
					if (!note[b][y][x]) {
						tmp[b][y][0]++;
						tmp[b][x][1]++;
						tmp[y][x][2]++;
						tmp[b][((((y*9)+x)/27)%27*3)+((((y*9)+x)/3)%3)][3]++;
					}
				}
			}
		}
		// Schritt 3: Alternativlose Felder mit Nummer setzen (zurück zu schritt 1)
		for (int a=0;a<9;++a) {
			for (int b=0;b<9;++b) {
				if (tmp[a][b][0]==1) {
					for (int c=0;c<9;++c) {
						if(!note[a][b][c]) {
							feld[b][c]=a+1;
//							std::cout << "0 X: " + std::to_string(c) + ", Y: " + std::to_string(b) + ", V: " + std::to_string(a+1) + "\n";
						}
					}
				}

				if (tmp[a][b][1]==1) {
					for (int c=0;c<9;++c) {
						if(!note[a][c][b]) {
							feld[c][b]=a+1;
//							std::cout << "1 X: " + std::to_string(b) + ", Y: " + std::to_string(c) + ", V: " + std::to_string(a+1) + "\n";
						}
					}
				}

				if (tmp[a][b][2]==1) {
					for (int c=0;c<9;++c) {
						if(!note[c][a][b]) {
							feld[a][b]=c+1;
//							std::cout << "2 X: " + std::to_string(b) + ", Y: " + std::to_string(a) + ", V: " + std::to_string(c+1) + "\n";
						}
					}
				}

				if (tmp[a][b][3]==1) {
					for (int c=0;c<9;++c) {
						int x=c%3+(b%3)*3;
						int y=c/3+(b/3)*3;
						if (!note[a][y][x]) {
							feld[y][x]=a+1;
//							std::cout << "3 X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", V: " + std::to_string(a+1) + "\n";
						}
					}
				}
			}
		}
	}
	printboard(feld);
	return 0;
}