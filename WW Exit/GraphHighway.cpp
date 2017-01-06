#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "GraphHighway.h"

// TODO: make code more modular

// TODO: implement illegal input checking
// Parses .CSV and loads values into adjMatrix
GraphHighway::GraphHighway(const std::string& FileLocation) 
{
	std::ifstream fAdjMatrix;
	fAdjMatrix.open(FileLocation);
	
	// for dumping unneccesary data from stream
	std::string dump;

	// load first line (contains node amount)
	fAdjMatrix >> numNodes;
	// skip rest of row after numNodes is read
	std::getline(fAdjMatrix, dump);

	// init adjMatrix (call def. constr. for edges)
	adjMatrix.resize(numNodes, std::vector<Edge>(numNodes));

	// algorithm for parsing .csv file, adding elements to adjMatrix
	for (int i = 1; i < numNodes; i++)
	{
		for (int j = 0; j < i; j++)
		{
			Edge &currEdge = adjMatrix.at(i).at(j);

			// check if edge exists by peeking for comma
			if (fAdjMatrix.peek() != ',')
			{
				currEdge.doesExist = true;
				fAdjMatrix >> currEdge.distanceDirect >> currEdge.speedLimit >> currEdge.toll;
				currEdge.distanceShortest = currEdge.distanceDirect;
				currEdge.minTravelTime = 60 * currEdge.distanceDirect /currEdge.speedLimit; // [1h = 60min]
			}

			else
			{
				// prepare non-diagonal non-existent edges for Floyd
				currEdge.distanceShortest = INFINITY;
				currEdge.minTravelTime = INFINITY;
			}

			// fill into symmetrical matrix element... [i][j] == [j][i]
			adjMatrix.at(j).at(i) = currEdge;

			// ignore comma
			fAdjMatrix.ignore(1);
		}

		// skip rest of row after all elements in BT matrix are read
		std::getline(fAdjMatrix, dump);
	}
	
	fAdjMatrix.close();

	floyd();
}

// TODO: avoid code repetition?
// calculates minTravelTime and toll between each node pair in graph
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
					ij.toll = ik.toll + kj.toll;
				}
			}
}

double GraphHighway::calcPrice(int startNode, int endNode, const double travelTime, const double penalty) const
{
	const Edge &currNode = adjMatrix.at(startNode - 1).at(endNode - 1);
	return currNode.toll + ((currNode.minTravelTime > travelTime) ? penalty : 0);
}

// DEBUG CODE
// FOR DEBUGGING PURPOSES, REMOVE IN PRODUCTION?
#ifdef DEBUG_MODE
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
			if (currNode.toll != 0.0)
				std::cout << currNode.toll;
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