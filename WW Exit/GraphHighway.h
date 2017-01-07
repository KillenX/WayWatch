#pragma once
#include "Matrix.h"
#include "debug.h"

// TODO: REWRITE GRAPH TO SUPPORT REQUIREMENTS!!!
class GraphHighway
{
private:
	struct Edge
	{
		bool doesExist			= false;// are nodes directly connected (without passing through other nodes)
		int speedLimit			= 0;	// speed limit between 2 connected nodes [km/h]
		double distanceDirect	= 0.0;	// direct travel distance between 2 connected nodes [km]
		double distanceShortest = 0.0;	// used in Floyd, minimum possible travel distance between 2 nodes [km]
		double minTravelTime	= 0.0;	// used in Floyd, minimum possible minimumTravelTime sum between 2 nodes [min]
		double toll				= 0.0;	// toll sum between 2 nodes (based on shortest distance path) [currency]
	};

	int numNodes;
	Matrix<Edge> adjMatrix; // symmetrical matrix

	// Floyd algorithm, sets distanceShortest, minTravelTime and toll values for all edges in adjMatrix
	void floyd(); 
public:
	GraphHighway() = delete;
	GraphHighway(const GraphHighway &) = delete;
	GraphHighway(GraphHighway &&) = delete;
	GraphHighway &operator=(const GraphHighway &) = delete;
	GraphHighway &operator=(GraphHighway &&) = delete;
	GraphHighway(const std::string& FileLocation);
	int getNumNodes();
	bool isConnected(const int startNode, const int endNode) const;
	double getToll(const int startNode, const int endNode) const;
	bool hasViolatedSpeedLimit(const int startNode, const int endNode, const double travelTime);
	
	#ifdef DEBUG_MODE
	void GraphHighway::draw() const;
	#endif
};

