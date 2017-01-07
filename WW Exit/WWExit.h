#pragma once
#include <functional>
#include <vector>
#include <string>
#include <utility>
#include "GraphHighway.h"

constexpr auto FILE_ADJ_MATRIX = "./data/AdjMatrix.csv";

class WWExit
{
private:
	using Function = std::function <void()>;
	using Option = std::pair <std::string, Function>;

	bool programExit;
	int tollBoothNumber;
	int tollBoothAmount; // the amount of toll booths on the highway, same as amount of nodes on highway graph
	std::vector <Option> options;
	GraphHighway graphHighway;

	bool validateSelection(std::istream &str, int selection);

	void printOptions();
	void initOptions();
	void generateReceipt();
	void readEntryCard();
	void tollPayment();
	void exit();
public:
	WWExit();
	WWExit(const WWExit &) = delete;
	WWExit(WWExit &&) = delete;
	WWExit &operator=(const WWExit &) = delete;
	WWExit &operator=(WWExit &&) = delete;
	void run();

};

