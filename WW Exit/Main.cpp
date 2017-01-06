#include <iostream>

#include "WWExit.h"
#include "Graph.h"

int main()
{
	Graph g(5);

	WWExit app(g.getNodeCount());

	app.run();
}