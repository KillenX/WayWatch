#include <iostream>
#include <fstream>
#include "Graph.h"




void Graph::doTaxes(int startNode, int endNode, int & toll)
{
	if (startNode == endNode)
		printf("%d", startNode);
	else if (pathMatrix[startNode][endNode] == -1)
		printf("Nema putanje\n");
	else
	{
		printf("%d-", endNode);
		doTaxes(startNode, pathMatrix[startNode][endNode], toll);
	}

}

void Graph::loadPaths(std::istream & str)
{
	loadArr<int>(str, pathMatrix);
}

void Graph::loadToll(std::istream & str)
{
	loadArr<float>(str, tollMatrix);
}

void Graph::loadLimits(std::istream & str)
{
	loadArr<int>(str, limitMatrix);
}

void Graph::loadDistances(std::istream & str)
{
	loadArr<float>(str, distMatrix);
}

void Graph::loadMinTime(std::istream & str)
{
	loadArr<float>(str, minTimeMatrix);
}

void Graph::savePaths(std::ostream & str)
{
	saveArr<int>(str, pathMatrix);
}

void Graph::saveToll(std::ostream & str)
{
	saveArr<float>(str, tollMatrix);
}

void Graph::saveMinTime(std::ostream & str)
{
	saveArr<float>(str, minTimeMatrix);
}


float Graph::getMinTime(int startNode, int endNode)
{
	return minTimeMatrix[startNode][endNode];
}

void Graph::floyd()
{
	for (int i = 0; i < nodeNo; i++)
	{
		for (int j = 0; j < nodeNo; j++)
		{
			for (int k = 0; k < nodeNo; k++)
			{
				if (minTimeMatrix[i][j] > minTimeMatrix[i][k] + minTimeMatrix[k][j])
				{
					minTimeMatrix[i][j] = minTimeMatrix[i][k] + minTimeMatrix[k][j];
					pathMatrix[i][j] = pathMatrix[k][j];
				}
			}
		}
	}
}

void Graph::calcMinTime()
{
	for (int i = 0; i < nodeNo; i++)
	{
		for (int j = 0; j < nodeNo; j++)
		{
			if (distMatrix[i][j] && limitMatrix[i][j])
				minTimeMatrix[i][j] = i == j ? 0 : (distMatrix[i][j] / limitMatrix[i][j] * 60);
			else
				minTimeMatrix[i][j] = i == j ? 0 : INT_MAX / 2;

			if (minTimeMatrix[i][j] == 0 || minTimeMatrix[i][j] == INT_MAX / 2)
				pathMatrix[i][j] = -1;
			else
				pathMatrix[i][j] = i;
		}
	}
}

void Graph::bootUp()  //does magic,dont touch
{

	std::ofstream minTimes, paths;
	std::fstream tolls, distances, limits;

	minTimes.open("MinimumTime.txt");
	paths.open("MinPaths.txt");
	distances.open("Distances.txt", std::ios::in);
	limits.open("SpeedLimits.txt", std::ios::in);
	tolls.open("Tolls.txt", std::ios::in);

	loadToll(tolls);
	loadDistances(distances);
	loadLimits(limits);

	calcMinTime();
	floyd();

	saveMinTime(minTimes);
	savePaths(paths);

	paths.close();
	minTimes.close();
	limits.close();
	distances.close();
	tolls.close();
}

int Graph::getNodeCount()
{
	return nodeNo;
}

Graph::Graph(int numberOfNodes) :nodeNo(numberOfNodes)
{
	distMatrix = new float*[nodeNo];
	limitMatrix = new int*[nodeNo];
	minTimeMatrix = new float*[nodeNo];
	pathMatrix = new int*[nodeNo];
	tollMatrix = new float*[nodeNo];

	for (int i = 0; i < nodeNo; i++)
	{
		tollMatrix[i] = new float[nodeNo];
		pathMatrix[i] = new int[nodeNo];
		minTimeMatrix[i] = new float[nodeNo];
		distMatrix[i] = new float[nodeNo];
		limitMatrix[i] = new int[nodeNo];
	}
}

Graph::~Graph()
{
	for (int i = 0; i < nodeNo; i++)
	{
		delete[] tollMatrix[i];
		delete[] pathMatrix[i];
		delete[] minTimeMatrix[i];
		delete[] limitMatrix[i];
		delete[] distMatrix[i];
	}
	delete[] distMatrix;
	delete[] limitMatrix;
	delete[] tollMatrix;
	delete[] pathMatrix;
	delete[] minTimeMatrix;
}
