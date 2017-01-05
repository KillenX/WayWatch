#include <iostream>
#include <fstream>
#include <ios>
#include "../common/UserManager.h"
#include "Graph.h"

using std::cout;
using std::ios;
using std::cin;


int main()
{
	Graph g(5);
	g.bootUp();

	

	cin.ignore();
	cin.get();
	return 0;
}