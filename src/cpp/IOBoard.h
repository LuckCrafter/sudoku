#pragma once
#include <fstream>
#include <iostream>
#include <string>
//#include <array>
#include "Board.h"

Board importBoard(std::string path);
void exportBoard(std::string path, Board const& board);
