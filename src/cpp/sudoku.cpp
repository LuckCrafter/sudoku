#include <iostream>
#include <array>
#include <fstream>
#include <string>
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

struct Board {
    int field[9][9] {};
	/*int feld[9][9] = {
	{6,0,0, 0,0,0, 0,0,4},
	{0,0,9, 0,8,0, 2,0,1},
	{0,3,0, 0,0,9, 0,0,0},

	{0,5,0, 1,0,0, 6,0,2},
	{0,0,0, 0,6,0, 0,3,0},
	{0,0,2, 0,0,0, 0,4,0},

	{0,0,0, 0,0,0, 0,6,0},
	{7,0,0, 5,0,0, 0,0,0},
	{0,0,3, 0,1,0, 8,0,9},
	};*/
	int& operator()(size_t y, size_t x) { return field[y][x]; }
	int operator()(size_t y, size_t x) const { return field[y][x]; }
};

std::string highlight = "\e[31m";
std::string highlight2 = "\e[32m";
std::string reset = "\e[0m";

struct Notes {
	bool note[9][9][9] {false}; // Schritt 0: Notizen erstellen und auf alle felder alle zahlen als notiz setzen
	bool& operator()(size_t b, size_t y, size_t x) { return note[b][y][x]; }
	bool operator()(size_t b, size_t y, size_t x) const { return note[b][y][x]; }
};

void printboard(Board const& board) {
	std::cout << "\n+-----+-----+-----+\n";
	for (int y=0;y<9;y++) {
		std::cout << '|';
		for (int x=0;x<9;x++) {
			int v = board(y, x);
			if (v == 0) std::cout << " ";
			else std::cout << v;
			if(x%3==2) {std::cout << "|"; }
			else { std::cout << " ";}
		}
		std::cout << "\n";
		if((y+1)%3+y/8==0) {std::cout << "+-----+-----+-----+\n";}
	}
	std::cout << "+-----+-----+-----+\n\n";
}

void printnote(Notes const& note) {
	for (int i=0;i<9;++i) {
		std::cout << "\n+-----+-----+-----+\n";
		for (int y=0;y<9;y++) {
			std::cout << '|';
			for (int x=0;x<9;x++) {
				bool v = note(i,y,x);
				if (v) std::cout << i+1;
				else std::cout << " ";
				if(x%3==2) {std::cout << "|"; }
				else { std::cout << " ";}
			}
			std::cout << "\n";
			if((y+1)%3+y/8==0) {std::cout << "+-----+-----+-----+\n";}
		}
		std::cout << "+-----+-----+-----+\n\n";
	}
}

void printboard(Board const& oldboard, Board const& board) {
	std::cout << "\n+-----+-----+-----+\n";
	Board tmp;
	for (int y=0;y<9;y++) {
		std::cout << '|';
		for (int x=0;x<9;x++) {
			if (board(y, x) != oldboard(y,x)) std::cout << highlight;
			else if (tmp(y,x)==0) std::cout<<highlight2;
			int v = board(y, x);
			if (v == 0) std::cout << " ";
			else std::cout << v;
			std::cout << reset;
			if(x%3==2) {std::cout << "|"; }
			else { std::cout << " ";}
		}
		std::cout << "\n";
		if((y+1)%3+y/8==0) {std::cout << "+-----+-----+-----+\n";}
	}
	std::cout << "+-----+-----+-----+\n\n";
}

void printboard(Board const& oldboard, Board const& board, Notes const& note) {
	std::cout << "\n+-----+-----+-----+\n";
	for (int y=0;y<9;y++) {
		std::cout << '|';
		for (int x=0;x<9;x++) {
			if (board(y, x) != oldboard(y,x)) std::cout << highlight;
			int v = board(y, x);
			if (v == 0) std::cout << " ";
			else std::cout << v;
			if (board(y, x) != oldboard(y,x)) std::cout << reset;
			if(x%3==2) {std::cout << "|"; }
			else { std::cout << " ";}
		}
		std::string notizen;
		for (int x=0;x<9;++x) {
			for (int i=0;i<9;++i) {
				if (!note(i,y,x)) {
					std::cout << std::to_string(i+1) + ",";
				}
			}
			if(x%8%3==2) { std::cout << "|"; }
			else { std::cout << " "; }
		}
		std::cout << notizen << "\n";
		if((y+1)%3+y/8==0) {std::cout << "+-----+-----+-----+\n";}
	}
	std::cout << "+-----+-----+-----+\n\n";
}

Board importBoard(std::string path, Board board) {
    std::ifstream input (path);
    if (input.is_open()) {
        //check if input.txt has a valid board(just 9x9 field)
        std::string line;
        int field[9][9] {0};
        int linenumber {0};
        int numperrow;
        while(getline(input,line)) {
            if (!line.empty()&&line[0]!='#'){
                int numperline = 0;
                for (int i = 0;i<=line.length();++i) {
                    if( line[i] >= '0' && line[i] <= '9' ) {
                        field[numperline][numperrow] = line[i] - '0';
                        ++numperline;
                    }
                }
                if (numperline == 9) {++numperrow;}
                else if (numperline != 0) {
                    input.close();
                    return board;
                }
            }
        }
        input.close();
        if (numperrow != 9) {return board;}
        //Board übertragen
        for(int i=0;i<81;++i) {board(i%9,i/9)=field[i%9][i/9];}
    } else {
        std::cout << "Can\'t open file\n";
    }
    return board;
}

void exportBoard(std::string path, Board& board) {
    std::ofstream output(path);
    if (!output.is_open()) {
        std::cout << "Can\'t open file\n";
        return;
    }
    output << "\n+-----+-----+-----+\n";
	for (int y=0;y<9;y++) {
		output << '|';
		for (int x=0;x<9;x++) {
			int v = board(y, x);
			if (v == 0) output << " ";
			else output << v;
			if(x%3==2) {output << "|"; }
			else { output << " ";}
		}
		output << "\n";
		if((y+1)%3+y/8==0) {output << "+-----+-----+-----+\n";}
	}
	output << "+-----+-----+-----+\n\n";
    output.close();
    return;
}

Notes generateNotes(Board const& board) {
	Notes note;
	//Schritt 1: Nummern von notizen entfernen die durch gesetze felder kollidieren
	for (int y=0;y<9;y++) {
		for (int x=0;x<9;x++) {
			if(board(y, x)!=0) {
				int b = board(y, x)-1;
				for (int i=0;i<9;i++) {
					note(b,y,i) = true; // remove horizontal
					note(b,i,x) = true; // remove verticale
					note(b,(y/3)*3+i%3,(x/3)*3+i/3) = true; // remove 3x3 cube
					note(i,y,x) = true; // remove all notes on the feld
				}
			}
		}
	}
	return note;
}

/*
Notes modNotes(int const& x,int const& y, bool& progress, Notes const& note) {
	//Schritt 1: Nummern von notizen entfernen die durch gesetze felder kollidieren
	if(board(y, x)) {
		int b = board(y, x)-1;
		for (int i=0;i<9;i++) {
			note(b,y,i) = true; // remove horizontal
			note(b,i,x) = true; // remove verticale
			note(b,(y/3)*3+i%3,(x/3)*3+i/3) = true; // remove 3x3 cube
			note(i,y,x) = true; // remove all notes on the feld
		}
	} else {
		progress=true;
	}
	return note;
}
*/

using Tmp = std::array<std::array<std::array<int, 4>, 9>, 9>;


Tmp schritt2(Notes const& note) {
	// Schritt 2: Prüfen ob es felder gibt die keine alternativen zahlen haben
	Tmp tmp{};
	for (int b=0;b<9;b++) {
		for (int y=0;y<9;y++) {
			for (int x=0;x<9;x++) {
				if (!note(b,y,x)) {
					tmp[b][y][0]++;
					tmp[b][x][1]++;
					tmp[y][x][2]++;
					tmp[b][((((y*9)+x)/27)%27*3)+((((y*9)+x)/3)%3)][3]++;
				}
			}
		}
	}
	return tmp;
}

bool finalBoard(Board const& board) {
	for (int i=0;i<81;++i) {
		if (board(i/9,i%9)==0) return false;
	}
	return true;
}

bool validBoard(Board const& board) {
	Notes const& note = generateNotes(board);
	Tmp tmp {};
	for (int a=0;a<9;++a) {
		for (int b=0;b<9;++b) {
			//tmp[a][b][3]=2;
			for (int c=0;c<9;++c) {
				if (board(a,b)==c+1) {
					tmp[c][a][0]++;
					tmp[c][b][1]++;
					tmp[c][((((a*9)+b)/27)%27*3)+((((a*9)+b)/3)%3)][2]++;
				}
				//if (board(a,b)==0 && note(c,a,b)) tmp[a][b][3]=0;
			}
		}
	}

	for (int j=0;j<3;++j) {
		for (int i=0;i<81;++i) {
			if ( tmp[i/9][i%9][j] > 1) return false;
		}
	}

	return true;
}

Board schritt3(Tmp const& tmp, Notes const& note, Board board) {
	// Schritt 3: Alternativlose Felder mit Nummer setzen (zurück zu schritt 1)
	for (int a=0;a<9;a++) {
		for (int b=0;b<9;b++) {
			if (tmp[a][b][0]==1) {
				for (int c=0;c<9;c++) {
					if(!note(a,b,c)) board(b, c)=a+1;
				}
			}

			if (tmp[a][b][1]==1) {
				for (int c=0;c<9;c++) {
					if(!note(a,c,b)) board(c, b)=a+1;
				}
			}

			if (tmp[a][b][2]==1) {
				for (int c=0;c<9;c++) {
					if(!note(c,a,b)) board(a, b)=c+1;
				}
			}

			if (tmp[a][b][3]==1) {
				for (int c=0;c<9;c++) {
					if (!note(a,c/3+(b/3)*3,c%3+(b%3)*3)) board(c/3+(b/3)*3, c%3+(b%3)*3)=a+1;
				}
			}
		}
	}
	return board;
}


Board smartSolving(Board const& realBoard) {
	Board board = realBoard;
	bool valid=true, progress=true;
	while (valid && progress) {
//		getchar(); // waits for enter
		progress=false;
		Notes note = generateNotes(board);
		Tmp tmp = schritt2(note);
		auto newBoard = schritt3(tmp, note, board);
//		printboard(board, newBoard, note);
		for (int i=0;i<81;++i) {
			if (board(i/9,i%9)!=newBoard(i/9,i%9)) {
				progress=true;
			}
		}
		board = newBoard;
		valid=validBoard(board);
	}
	if (valid) return board;
	return realBoard;
}

Board smartbruteforce(Board const& RealBoard) {
	Board board;
	//std::cout<<"\nStarting smart Bruteforcing!\n";
	bool progress=true;
	Notes notes=generateNotes(RealBoard);
	for (int y=0;y<9;++y) {
		for (int x=0;x<9;++x) {
			if (RealBoard(y,x)==0) {
				for (int b=0;b<9;++b) {
					if(!notes(b,y,x)) {
//						getchar();
						board=RealBoard;
						board(y,x)=b+1;
//						printboard(RealBoard,board);
						board = smartSolving(board);
						if (!finalBoard(board)) board = smartbruteforce(board);
						if (finalBoard(board)) return board;
					}
				}
				return RealBoard;
			}
		}
	}
	return RealBoard;
}

Board dumpbruteforce(Board const& RealBoard) {
	Board board;
	//std::cout<<"\nStarting Bruteforcing!\n";
	bool progress=true;
	Notes notes=generateNotes(RealBoard);
	for (int y=0;y<9;++y) {
		for (int x=0;x<9;++x) {
			if (RealBoard(y,x)==0) {
				for (int b=0;b<9;++b) {
					if(!notes(b,y,x)) {
//						getchar();
						board=RealBoard;
						board(y,x)=b+1;
//						printboard(RealBoard,board);
						if (validBoard(board)&&!finalBoard(board)) board = dumpbruteforce(board);
						if (finalBoard(board)) return board;
						//std::cout << "failed, try next number";
					}
				}
				return RealBoard;
			}

		}
	}
	return RealBoard;
}

Board bruteforce(Board const& board, bool smart) {
	if (smart) return smartbruteforce(board);
	else return dumpbruteforce(board);
}

int main() {
    Board board, smartboard, bruteboard;
    board = importBoard("./input.txt", board);
//    printboard(board);
	bool smart = true;
//	printboard(board);
    //smartboard = smartSolving(board);
	//printboard(board,smartboard);
	bruteboard = bruteforce(board,smart);
	printboard(board,bruteboard);
    exportBoard("./output.txt", bruteboard);
	return !finalBoard(bruteboard);
}
