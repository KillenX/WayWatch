#pragma once
#include <string>

class Receipt
{
private:
	std::string vehicleCategory;
	std::string entryDateTime;
	std::string exitDateTime;

	int entryNumber;
	int exitNumber;
	int receiptNumber;

	double price;
public:
	Receipt(std::string entryDate, int entryNode, std::string exitDate, int exitNode, std::string vCategory, double price, bool hasViolated, int rNumber);

	void printReceiptHeader(std::ostream &str);
	void printReceipt(std::ostream &str);
};