#pragma once
#include <string>

class Receipt
{
private:
	std::string entryDateTime;
	int entryNode;
	std::string exitDateTime;
	int exitNode;
	std::string vehicleCategory;
	double price;
	bool hasViolated;
public:
	Receipt(std::string entryDate, int entryNode,
		std::string exitDate, int exitNode,
		std::string vCategory, double price, bool hasViolated);
	void printReceiptHeader(std::ostream &str);
	void printReceipt(std::ostream &str);
};