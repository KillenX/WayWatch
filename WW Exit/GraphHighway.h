#pragma once
#include "Matrix.h"
#include "../common/debug.h"
#include "../common/CsvParser.h"
#include <map>

class GraphHighway
{
public:
	GraphHighway();
	GraphHighway(const GraphHighway &) = delete;
	GraphHighway(GraphHighway &&) = delete;
	GraphHighway &operator=(const GraphHighway &) = delete;
	GraphHighway &operator=(GraphHighway &&) = delete;
	int getNumNodes();
	bool isConnected(const int startNode, const int endNode) const;
	double getToll(const int startNode, const int endNode, const std::string &category) const;
	bool hasViolatedSpeedLimit(const int startNode, const int endNode, const double travelTime) const;
#ifdef DEBUG_MODE
	void GraphHighway::draw() const;
#endif
private:
	struct Edge
	{
		bool doesExist = false;// are nodes directly connected (without passing through other nodes)
		int speedLimit = 0;	// speed limit between 2 connected nodes [km/h]
		double distanceDirect = 0.0; // direct travel distance between 2 connected nodes [km]
		double distanceShortest = 0.0;	// used in Floyd, minimum possible travel distance between 2 nodes [km]
		double minTravelTime = 0.0;	// used in Floyd, minimum possible minimumTravelTime sum between 2 nodes [min]
		std::map<std::string, double> tolls; // // toll sums between 2 nodes (based on shortest distance path) [currency]
	};

	int numNodes;	
	Matrix<Edge> adjMatrix; // symmetrical matrix
	std::vector<std::string> vehicleCategories;
	void loadAdjMatrix();
	void loadEdgeData();
	void floyd(); // Floyd algorithm, sets distanceShortest, minTravelTime and toll values for all edges in adjMatrix
};

