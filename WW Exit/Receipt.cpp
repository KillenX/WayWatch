#include "Receipt.h"
#include "../common/Constants.h"
#include <iomanip>


Receipt::Receipt(std::string entryDate, int entryNode,
	std::string exitDate, int exitNode,
	std::string vCategory, double price, bool hasViolated)
	: entryDateTime(entryDate)
	, entryNode(entryNode)
	, exitDateTime(exitDate)
	, exitNode(exitNode)
	, vehicleCategory(vCategory)
	, price(price)
	, hasViolated(hasViolated) {}

void Receipt::printReceiptHeader(std::ostream &str)
{
	str << "===========================================" << std::endl;
}

void Receipt::printReceipt(std::ostream &str)
{
	printReceiptHeader(str);

	str << std::setw(22) << std::left << "Entry node:" << entryNode << std::endl
		<< std::setw(22) << std::left << "Entry date and time:" << entryDateTime << std::endl
		<< std::setw(22) << std::left << "Exit node:" << exitNode << std::endl
		<< std::setw(22) << std::left << "Exit date and time:" << exitDateTime << std::endl
		<< std::setw(22) << std::left << "Vehicle category:" << vehicleCategory << std::endl
		<< std::setw(22) << std::left << "Violation:" << (hasViolated ? "YES" : "NO") << std::endl
		<< std::setw(22) << std::left << "Price:" << price << " " << CURRENCY << std::endl;

	printReceiptHeader(str);
}
