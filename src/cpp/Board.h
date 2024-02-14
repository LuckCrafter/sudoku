#pragma once
#include <cstddef>

struct Board {
    private int field[9][9] {0};
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

  	private bool notes[9][9][9] {false};
	bool& note(size_t b, size_t y, size_t x) {return notes[b][y][x];}
	bool note(size_t b, size_t y, size_t x) const {return notes[b][y][x];}
	void genNotes() {
		for (int y=0;y<9;y++) {
			for (int x=0;x<9;x++) {
				if(field[y][x]!=0) {
					int b = field[y][x]-1;
					for (int i=0;i<9;i++) {
						notes[b][y][i] = true; // remove horizontal
						notes[b][i][x] = true; // remove verticale
						notes[b][(y/3)*3+i%3][(x/3)*3+i/3] = true; // remove 3x3 cube
						notes[i][y][x] = true; // remove all notes on the feld
					}
				}
			}
		}
	}
};
/*
struct Notes {
	bool note[9][9][9] {false}; // Schritt 0: Notizen erstellen und auf alle felder alle zahlen als notiz setzen
	bool& operator()(size_t b, size_t y, size_t x) { return note[b][y][x]; }
	bool operator()(size_t b, size_t y, size_t x) const { return note[b][y][x]; }
};
*/
