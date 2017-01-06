#include <iostream>
#include <fstream>
#include <ios>
#include "../common/UserManager.h"
#include "GraphHighway.h"

constexpr auto FILE_ADJ_MATRIX = "./data/AdjMatrix.csv";

int main()
{
	GraphHighway graphHighway(FILE_ADJ_MATRIX);
	graphHighway.draw();

	
	std::cout << std::endl << graphHighway.calcPrice(1, 2, 1, 50);
	
	std::cin.ignore();
	std::cin.get();
	return 0;
}