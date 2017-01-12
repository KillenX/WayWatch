#include "GraphHighway.h"
#include "../common/Constants.h"
#include "../common/Properties.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

GraphHighway::GraphHighway()
{
	numNodes = Properties::getNumNodes();
	adjMatrix.resize(numNodes, std::vector<Edge>(numNodes));
	CsvParser csvParser;
	csvParser.open(FILE_GRAPH_DATA);

	// skip first two lines
	csvParser.goNextLine(2); 

	while (!csvParser.reachedEOF())
	{
		int nodeA, nodeB;

		csvParser >> nodeA;
		csvParser.goNextCol();
		csvParser >> nodeB;

		// Can't have self-loops.
		if (nodeA == nodeB)
		{
			csvParser.goNextLine();
			return;
		}

		// Zero indexing.
		int i = nodeA - 1;
		int j = nodeB - 1;

		Edge &edge = adjMatrix.at(i).at(j);

		edge.doesExist = true;
		csvParser.goNextCol();
		csvParser >> edge.distanceDirect;
		csvParser.goNextCol();
		csvParser >> edge.speedLimit;
		csvParser.goNextCol();

		for (const std::string &category : Properties::getVehicleCategories())
		{
			double price;
			csvParser >> price;
			edge.tolls.emplace(category, price);
			csvParser.goNextCol();
		}

		edge.distanceShortest = edge.distanceDirect;
		edge.minTravelTime = 60 * edge.distanceDirect / edge.speedLimit; // [1h = 60min]

		// Set it's symmetryic counterpart element
		adjMatrix.at(j).at(i) = edge;

		csvParser.goNextLine();
	}

	csvParser.close();
	floyd();
}

void GraphHighway::floyd()
{
	// Necessary to set it up like this for Floyd's algorithm to work.
	for (int i = 0; i < numNodes; i++)
		for (int j = 0; j < numNodes; j++)
		{
			Edge &edge = adjMatrix.at(i).at(j);
			if (!edge.doesExist)
			{
				for (const std::string &category : Properties::getVehicleCategories())
					edge.tolls.emplace(category, 0.0);
				edge.distanceShortest = edge.minTravelTime = (i == j) ? 0 : INFINITY;
			}
		}

	for (int i = 0; i < numNodes; i++)
		for (int j = 0; j < numNodes; j++)
			for (int k = 0; k < numNodes; k++)
			{
				Edge &ij = adjMatrix.at(i).at(j);
				Edge &ik = adjMatrix.at(i).at(k);
				Edge &kj = adjMatrix.at(k).at(j);

				if (ij.minTravelTime > ik.minTravelTime + kj.minTravelTime)
					ij.minTravelTime = ik.minTravelTime + kj.minTravelTime;

				if (ij.distanceShortest > ik.distanceShortest + kj.distanceShortest)
				{
					ij.distanceShortest = ik.distanceShortest + kj.distanceShortest;
					for (const std::string &category : Properties::getVehicleCategories())
						ij.tolls.at(category) = ik.tolls.at(category) + kj.tolls.at(category);
				}
			}
}

int GraphHighway::getNumNodes()
{
	return numNodes;
}

bool GraphHighway::isConnected(const int startNode, const int endNode) const
{
	const Edge &edge = adjMatrix.at(startNode - 1).at(endNode - 1);

	if (edge.doesExist)
		return true;

	if ((edge.distanceShortest == INFINITY) || (edge.distanceShortest == 0.0))
		return false;

	return true;
}

double GraphHighway::getToll(const int startNode, const int endNode, const std::string &category) const
{
	return adjMatrix.at(startNode - 1).at(endNode - 1).tolls.at(category);
}

bool GraphHighway::hasViolatedSpeedLimit(const int startNode, const int endNode, const double travelTime) const
{
	return ((adjMatrix.at(startNode - 1).at(endNode - 1).minTravelTime > travelTime) ? true : false);
}

#ifdef DEBUG_MODE
// **********************************************
// DEBUG CODE
// FOR DEBUGGING PURPOSES, REMOVE IN PRODUCTION?
// **********************************************
void GraphHighway::draw() const
{
	static const int FILL_WIDTH = 5;
	static const int PADDING_LEFT = 4;

	// add left padding to next line
	std::cout << std::endl << std::setw(PADDING_LEFT);

	// write out column numbers
	for (int i = 0; i < numNodes; i++)
		std::cout << ' ' << i + 1 << std::setw(FILL_WIDTH - 1);

	// add left padding to next line
	std::cout << std::endl << std::setw(PADDING_LEFT);

	// write out first border line
	std::cout << '+';
	std::cout << std::setfill('-');
	for (int j = 0; j < numNodes; j++)
		std::cout << std::setw(FILL_WIDTH) << '+';

	// reset fill
	std::cout << std::setfill(' ');

	for (int i = 0; i < numNodes; i++)
	{
		std::cout << std::left;

		// add left padding to next line, reduced by 1 for proper alignment
		std::cout << std::endl << std::setw(PADDING_LEFT - 1);

		// write out row number
		std::cout << i + 1 << '|';

		// write out data
		for (int j = 0; j < numNodes; j++)
		{
			// set left-align
			std::cout << std::left;

			// set padding
			std::cout << std::setw(FILL_WIDTH - 1);

			// write out element
			const Edge &currNode = adjMatrix.at(i).at(j);
			if (currNode.minTravelTime != 0.0)
				std::cout << currNode.tolls.at("D");
			else std::cout << ' ';
			std::cout << '|';

			// reset to right-align
			std::cout << std::right;
		}

		std::cout << std::endl << std::setw(PADDING_LEFT);
		std::cout << '+' << std::setfill('-');

		// write out bottom border
		for (int j = 0; j < numNodes; j++)
			std::cout << std::setw(FILL_WIDTH) << '+';

		// reset fill
		std::cout << std::setfill(' ');
	}

	std::cout << std::endl;
}
#endif