#pragma once
#include <fstream>
#include "Matrix.h"
#include "debug.h"
class GraphHighway
{
private:
	struct Edge
	{
		bool doesExist = false;	// are nodes physically connected?
		int speedLimit = 0;		// speed limit between 2 connected nodes [km/h]
		double distanceDirect = 0.0;	// direct travel distance between 2 connected nodes [km]
		double distanceShortest = 0.0; // used in Floyd, minimum possible travel distance between 2 nodes [km]
		double minTravelTime = 0.0;	// used in Floyd, minimum possible minimumTravelTime sum between 2 nodes [min]
		double toll = 0.0;			// toll sum between 2 nodes (based on shortest distance path) [currency]
	};
	int numNodes;
	Matrix<Edge> adjMatrix; // symmetrical matrix

	void floyd(); // Floyd algorithm, sets distanceShortest, minTravelTime and toll values for all edges in adjMatrix
public:
	GraphHighway() = delete;
	GraphHighway(const std::string& FileLocation);
	double calcPrice(const int startNode, const int endNode, const double travelTime, const double penalty) const;

	#ifdef DEBUG_MODE
	void GraphHighway::draw() const;
	#endif
};

