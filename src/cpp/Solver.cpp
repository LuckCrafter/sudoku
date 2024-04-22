#include "Solver.h"

//needed check funcs
bool finalBoard(Board const& board) {
	for (int i=0;i<81;++i) {
		if (board(i/9,i%9)==0) return false;
	}
	return true;
}

bool validBoard(Board const& board) {
	IntArray tmp {};
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

//Start
/*
Board generateNotes(Board board) {
	//Notes note;
	//Schritt 1: Nummern von notizen entfernen die durch gesetze felder kollidieren
	for (int y=0;y<9;y++) {
		for (int x=0;x<9;x++) {
			if(board(y, x)!=0) {
				int b = board(y, x)-1;
				for (int i=0;i<9;i++) {
					board.note(b,y,i) = true; // remove horizontal
					board.note(b,i,x) = true; // remove verticale
					board.note(b,(y/3)*3+i%3,(x/3)*3+i/3) = true; // remove 3x3 cube
					board.note(i,y,x) = true; // remove all notes on the feld
				}
			}
		}
	}
	return board;
}
*/
IntArray schritt2(Board const& board) {
	// Schritt 2: Prüfen ob es felder gibt die keine alternativen zahlen haben
	IntArray tmp{};
	for (int b=0;b<9;b++) {
		for (int y=0;y<9;y++) {
			for (int x=0;x<9;x++) {
				if (!board.note(b,y,x)) {
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



Board schritt3(IntArray const tmp, Board& board) {
	// Schritt 3: Alternativlose Felder mit Nummer setzen (zurück zu schritt 1)
	for (int a=0;a<9;a++) {
		for (int b=0;b<9;b++) {
			if (tmp[a][b][0]==1) {
				for (int c=0;c<9;c++) {
					if(!board.note(a,b,c)) board(b, c)=a+1;
				}
			}

			if (tmp[a][b][1]==1) {
				for (int c=0;c<9;c++) {
					if(!board.note(a,c,b)) board(c, b)=a+1;
				}
			}

			if (tmp[a][b][2]==1) {
				for (int c=0;c<9;c++) {
					if(!board.note(c,a,b)) board(a, b)=c+1;
				}
			}

			if (tmp[a][b][3]==1) {
				for (int c=0;c<9;c++) {
					if (!board.note(a,c/3+(b/3)*3,c%3+(b%3)*3)) board(c/3+(b/3)*3, c%3+(b%3)*3)=a+1;
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
		//board = generateNotes(board);
		board.genNotes();
		IntArray tmp = schritt2(board);
		Board newBoard = schritt3(tmp, board);
		printnote(newBoard, board);
        std::cout << "\n\n";
		for (int i=0;i<81;++i) {
			if (board(i/9,i%9)!=newBoard(i/9,i%9)) {progress=true;}
		}
		board = newBoard;
		valid=validBoard(board);
        std::cout << valid;
	}
	if (valid) return board;
	return realBoard;
}

Board smartbruteforce(Board const& realBoard) {
	Board board = realBoard;
	//std::cout<<"\nStarting smart Bruteforcing!\n";
	//board = generateNotes(RealBoard);
	board.genNotes();
    std::cout << "Hey\n";
	for (int y=0;y<9;++y) {
		for (int x=0;x<9;++x) {
			if (board(y,x)==0) {
				for (int b=0;b<9;++b) {
					if(!board.note(b,y,x)) {
//						getchar();
						board=realBoard;
						board(y,x)=b+1;
//						printboard(RealBoard,board);
						board = smartSolving(board);
						if (!finalBoard(board)) board = smartbruteforce(board);
						if (finalBoard(board)) return board;
					}
				}
				return realBoard;
			}
		}
	}
    Board newBoard;
	return newBoard;
}

Board dumpbruteforce(Board const& realBoard) {
	Board board = realBoard;
	//std::cout<<"\nStarting Bruteforcing!\n";
	//board = generateNotes(RealBoard);
	board.genNotes();
	for (int y=0;y<9;++y) {
		for (int x=0;x<9;++x) {
			if (realBoard(y,x)==0) {
				for (int b=0;b<9;++b) {
					if(!board.note(b,y,x)) {
//						getchar();
						board=realBoard;
						board(y,x)=b+1;
//						printboard(RealBoard,board);
						if (validBoard(board)&&!finalBoard(board)) board = dumpbruteforce(board);
						if (finalBoard(board)) return board;
						//std::cout << "failed, try next number";
					}
				}
				return realBoard;
			}

		}
	}
	return realBoard;
}

Board bruteforce(Board const& board, bool smart) {
	if (smart) return smartbruteforce(board);
	else return dumpbruteforce(board);
}

