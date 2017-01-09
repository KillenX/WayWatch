#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "GraphHighway.h"

// TODO: make code more modular
// TODO: implement illegal input checking
// TODO: rewrite comments
// TODO: if EdgeData doesn't contain all edges make it ERROR, bad results otherwise

GraphHighway::GraphHighway() 
{
	loadAdjMatrix();
	loadEdgeData();
	floyd();
}

void GraphHighway::loadAdjMatrix()
{
	CsvParser csvParser;
	csvParser.open(FILE_ADJ_MATRIX);

	// load first line (contains node amount)
	csvParser >> numNodes;

	// skip rest of row after numNodes is read
	csvParser.goNextLine();

	// init adjMatrix (call def. constr. for edges)
	adjMatrix.resize(numNodes, std::vector<Edge>(numNodes));

	// algorithm for parsing .csv file, adding elements to adjMatrix
	for (int i = 1; i < numNodes; i++)
	{
		for (int j = 0; j < i; j++)
		{
			Edge &currEdge = adjMatrix.at(i).at(j);

			// check if edge exists
			if (!csvParser.currentCellEnded())
				currEdge.doesExist = true; // should be constructor-initialized to false otherwise

			else
			{
				// prepare non-diagonal non-existent edges for Floyd
				currEdge.distanceShortest = INFINITY;
				currEdge.minTravelTime = INFINITY;
			}

			// fill into symmetrical matrix element... [i][j] == [j][i]
			adjMatrix.at(j).at(i) = currEdge; 

			csvParser.goNextCol();
		}

		// skip rest of row after all elements in bottom triangular matrix row are read
		csvParser.goNextLine();
	}

	csvParser.close();
}

void GraphHighway::loadEdgeData()
{
	CsvParser csvParser;
	csvParser.open(FILE_EDGE_DATA);
	csvParser.goNextCol(4); // skip unecessary header part
	
	// Load vehicle categories

	while (!csvParser.currentLineEnded())
	{
		std::string temp;
		csvParser >> temp;
		vehicleCategories.push_back(temp);
		csvParser.goNextCol(); // definitely find better way plz
	}

	// prepare tolls map for floyd (if disconnected edges not init to 0, subscripting is out of range in Floyd's algorithm) -- PERHAPS merge loadEdgeData and loadAdjMatrix?
	for (std::vector<Edge>& vector : adjMatrix)
		for (Edge& edge : vector)
		{
			if (!edge.doesExist)
			for (const std::string &category : vehicleCategories)
				edge.tolls.try_emplace(category, 0.0);
		}

	csvParser.goNextLine();
	
	// load nodes
	// move to function
	while (!csvParser.reachedEOF())
	{
		int nodeA, nodeB;

		csvParser >> nodeA;
		csvParser.goNextCol();
		csvParser >> nodeB;
		csvParser.goNextCol();

		// zero indexing prep.
		nodeA--;
		nodeB--;

		Edge &currEdge = adjMatrix.at(nodeA).at(nodeB);

		// TODO: error if not connected
		if (currEdge.doesExist)
		{
			csvParser >> currEdge.distanceDirect;
			csvParser.goNextCol();
			csvParser >> currEdge.speedLimit;
			csvParser.goNextCol();

			// is it guaranteed that the order of categories in table is same as in vector? hopefully yes
			// hopefully also guaranteed we won't fall into next line.
			// what about undefined tolls in table? hopefully everything is set to something in EdgeData
			// we're hoping too much?
			for (const std::string &category : vehicleCategories)
			{
				double price;
				csvParser >> price;
				currEdge.tolls.try_emplace(category, price);
				csvParser.goNextCol(); // goes to next line on last cell hopefully
			}

			currEdge.distanceShortest = currEdge.distanceDirect;
			currEdge.minTravelTime = 60 * currEdge.distanceDirect / currEdge.speedLimit; // [1h = 60min]

			adjMatrix.at(nodeB).at(nodeA) = currEdge; // sets symmetric element to be the same. bcz symmetric.
		}

		csvParser.goNextLine();
	}

	csvParser.close();
}

// calculates minTravelTime and toll per category between each node pair in graph
// function should be reimplemented based on future plans?
void GraphHighway::floyd()
{
	// make sure non-diagonal non-existent edges had minTravelTime and distanceShortest set to INFINITY
	// make sure diagonal edges had everything set to 0
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
					for (const std::string &category : vehicleCategories)
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
	const Edge &currNode = adjMatrix.at(startNode - 1).at(endNode - 1);
	if (currNode.doesExist)
		return true;

	if ((currNode.distanceShortest == INFINITY) || (currNode.distanceShortest == 0.0))
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
	const int FILL_WIDTH = 5;
	const int PADDING_LEFT = 4;

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
		// set left-align
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
				std::cout << currNode.tolls.at("A");
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