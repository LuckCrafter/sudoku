#pragma once
#include "Board.h"
#include <string>
#include <iostream>

void printboard(Board); //printboard
void printnote(Board);  //print notes (9 boards, for every number one)
void printboard(Board, Board);  // compare both boards and highligths diffrence
void printnote(Board, Board); // combind the both