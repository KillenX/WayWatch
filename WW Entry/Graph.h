#pragma once
#include <iostream>

class Graph
{
	int nodeNo;
	int   **pathMatrix;		//najkraci put, za rekonstrukciju putanje
	int   **limitMatrix;	//u km/h
	float **distMatrix;		//u kilometrima
	float **minTimeMatrix;  //u minutama najkraci put izmedju 2 cvora
	float **tollMatrix;		//putarine

	template<typename T>
	void saveArr(std::ostream& str, T**);
	template<typename T>
	void loadArr(std::istream& str, T**);
	
public:
	void doTaxes(int startNode, int endNode, int &toll);//ne radi trenutno

	void loadPaths(std::istream& str);
	void loadToll(std::istream& str);
	void loadLimits(std::istream& str);
	void loadDistances(std::istream& str);
	void loadMinTime(std::istream& str);

	void savePaths(std::ostream& str);
	void saveToll(std::ostream& str);
	void saveMinTime(std::ostream& str);

	float getMinTime(int startNode, int endNode);	//vraca najmanje vrijeme neophodno za prolaz izmedju 2 cvora
	void  floyd();									//racuna najkrace vrijeme za putovanje izmedju 2 cvora u minutama i putarinu
	void  calcMinTime();							//racuna najkraca vremena prolaska na dionicama
	void bootUp();


	Graph(int numberOfNodes);
	~Graph();
};

template<typename T>
inline void Graph::saveArr(std::ostream & str, T **arr)
{
	str << nodeNo << std::endl;
	for (int i = 0; i < nodeNo; i++)
	{
		for (int j = 0; j < nodeNo; j++)
		{
			str << arr[i][j] << " ";
		}
		str << std::endl;
	}
}

template<typename T>
inline void Graph::loadArr(std::istream & str, T **arr)
{
	str >> nodeNo;
	for (int i = 0; i < nodeNo; i++)
	{
		for (int j = 0; j < nodeNo; j++)
		{
			str >> arr[i][j];
		}
	}

}
