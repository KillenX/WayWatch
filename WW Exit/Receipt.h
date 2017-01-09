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
	int receiptNumber;	
public:
	Receipt(std::string entryDate, int entryNode, 
		std::string exitDate, int exitNode, 
		std::string vCategory, double price, bool hasViolated, 
		int receiptNumber);
	void printReceiptHeader(std::ostream &str);
	void printReceipt(std::ostream &str);
};