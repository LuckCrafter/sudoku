#include "Print.h"

std::string highlight = "\e[31m";
std::string highlight2 = "\e[32m";
std::string reset = "\e[0m";

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
/*
void printnote(Board const board) {
	for (int i=0;i<9;++i) {
		std::cout << "\n+-----+-----+-----+\n";
		for (int y=0;y<9;y++) {
			std::cout << '|';
			for (int x=0;x<9;x++) {
				bool v = board.note(i,y,x);
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
*/
void printnote(Board const& board) {
	for (int y {0};y<27;++y) {
		if (y%3==0) {std::cout << "+–––+---+---+ +---+---+---+ +---+---+---+\n";}
		for (int x {0};x<27;++x) {
			if (x%3==0) {std::cout << "|";}
			if (board(y/3,x/3)!=0) {
				if (x%3==1&&y%3==1) {std::cout << "\033[1;1m" << board(y/3,x/3) << reset;}
				else {std::cout << " ";}
			}
			else {
				if (!board.note(x%3+(y%3*3),y/3,x/3)) {std::cout <<  x%3+(y%3*3)+1;}
				else {std::cout << " ";}
			}
			if (x%9==8) {std::cout << "| ";}
		}
		std::cout << std::endl;
		if (y%9==8) {std::cout << "+–––+---+---+ +---+---+---+ +---+---+---+\n";}
	}
}

void printboard(Board const& oldboard, Board const& board) {
	std::cout << "\n+-----+-----+-----+\n";
	for (int y=0;y<9;y++) {
		std::cout << '|';
		for (int x=0;x<9;x++) {
			if (board(y, x) != oldboard(y,x)) std::cout << highlight;
			else std::cout<<highlight2;
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
/*
void printnote(Board const& oldboard, Board const& board) {
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
				if (!board.note(i,y,x)) {
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
*/
void printnote(Board const& oldboard, Board const& board) {
    for (int y {0};y<27;++y) {
        if (y%3==0) {std::cout << "+–––+---+---+ +---+---+---+ +---+---+---+\n";}
        for (int x {0};x<27;++x) {
            if (x%3==0) {std::cout << "|";}
            if (board(y/3,x/3)!=0) {
                if (x%3==1&&y%3==1) {
                    if (board(y/3,x/3) != oldboard(y/3,x/3)) {std::cout << highlight;}
                    else {std::cout << highlight2;}
                    std::cout << board(y/3,x/3) << reset;
                }
                else {std::cout << " ";}
            }
            else {
                if (!board.note(x%3+(y%3*3),y/3,x/3)) {std::cout <<  x%3+(y%3*3)+1;}
                else {std::cout << " ";}
            }
            if (x%9==8) {std::cout << "| ";}
        }
        std::cout << std::endl;
        if (y%9==8) {std::cout << "+–––+---+---+ +---+---+---+ +---+---+---+\n";}
    }
}
