#include "IOBoard.h"

Board importBoard(std::string path) {
    std::ifstream input (path);
    if (!input.is_open()) {
        std::cout << "Can\'t open file\n";
        throw std::runtime_error{"file not found"};
    }
    //check if input.txt has a valid board(just 9x9 field)
    std::string line;
    Board board;
    int numperrow {0};
    while(getline(input,line)) {
        if (line.empty() || line[0]=='#') continue;
        int numperline = 0;
        for (size_t i = 0;i<line.length();++i) {
            if( line[i] >= '0' && line[i] <= '9' ) {
                board(numperline, numperrow) = line[i] - '0';
                ++numperline;
            }
        }
        if (numperline == 9) {++numperrow;}
        else if (numperline != 0) {
            throw std::runtime_error{"not correct format"};
        }
    }
    input.close();
    if (numperrow != 9) {throw std::runtime_error{"not correct format"};}
    //Board übertragen
    //for(int i=0;i<81;++i) {board(i%9,i/9)=field[i%9][i/9];}
    return board;
}

void exportBoard(std::string path, Board board) {
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