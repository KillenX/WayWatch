#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "GraphHighway.h"

#include <exception>

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

			// ignore up to next comma in .csv
			fAdjMatrix.ignore(INT_MAX, ',');
		}

		// skip rest of row after all elements in bottom triangular matrix row are read
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

	if (!edgeValidityCheck()) //add edgeValidityCheck 
	{
		std::runtime_error edgeNotValide("ERROR: Edge is not valide");
		throw edgeNotValide;
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
					ij.toll = ik.toll + kj.toll;
				}
			}
}

bool GraphHighway::edgeValidityCheck()
{
	for (int i = 0; i < numNodes; ++i)
	{
		Edge &ii = adjMatrix.at(i).at(i);
		if (!ii.everythingZero())
		{
			return false;
		}
	}
	for (int i = 0; i < numNodes; ++i)
		for (int j = 0; j < numNodes; ++j)
		{
			Edge &ii = adjMatrix.at(i).at(j);
			if (!ii.isValideNonDiagonalEdge())
			{
				return false;
			}
		}
	return true;
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

double GraphHighway::getToll(const int startNode, const int endNode) const
{
	return adjMatrix.at(startNode - 1).at(endNode - 1).toll;
}

bool GraphHighway::hasViolatedSpeedLimit(const int startNode, const int endNode, const double travelTime)
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

bool GraphHighway::Edge::everythingZero()
{
	return doesExist == false && speedLimit == 0 && distanceDirect == 0.0 && distanceShortest == 0.0 && minTravelTime == 0.0 && toll == 0.0;
}

bool GraphHighway::Edge::isValideNonDiagonalEdge()
{
	if (doesExist)
		return true;
	else return distanceShortest == INFINITY && minTravelTime == INFINITY;
}
