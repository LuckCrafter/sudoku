#pragma once
#include <fstream>
#include <iostream>
#include <string>
//#include <array>
#include "Board.h"

Board importBoard(std::string);
void exportBoard(std::string, Board);