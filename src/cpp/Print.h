#pragma once
#include "Board.h"
#include <string>
#include <iostream>

void printboard(Board const& board); //printboard
void printnote(Board const& board);  //print notes (9 boards, for every number one)
void printboard(Board const& board, Board const& oldboard);  // compare both boards and highligths diffrence
void printnote(Board const& board, Board const& oldboard); // combind the both
