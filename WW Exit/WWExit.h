#pragma once
#include <functional>
#include <vector>
#include <string>
#include <utility>
#include "GraphHighway.h"
#include "Receipt.h"

class WWExit
{
private:
	using Function = std::function <void()>;
	using Option = std::pair <std::string, Function>;

	bool programExit;
	int tollBoothNumber; // id. number of node the employee is located at
	int tollBoothAmount; // amount of nodes on highway graph
	std::vector <Option> options;
	GraphHighway graphHighway;

	bool validateSelection(std::istream &str, int botLimit, int topLimit, int number);
	void inputTollBoothNumber();

	void printOptions() const;
	void initOptions();
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

