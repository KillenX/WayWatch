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
	str << "============================================" << std::endl;
}

void Receipt::printReceipt(std::ostream &str)
{
	printReceiptHeader(str);

	str << std::setw(25) << std::left << "Ulazni cvor:" << entryNode << std::endl
		<< std::setw(25) << std::left << "Vrijeme ulaza:" << entryDateTime << std::endl
		<< std::setw(25) << std::left << "Izlazni cvor:" << exitNode << std::endl
		<< std::setw(25) << std::left << "Vrijeme izlaza:" << exitDateTime << std::endl
		<< std::setw(25) << std::left << "Kategorija vozila:" << vehicleCategory << std::endl
		<< std::setw(25) << std::left << "Napravljen prekrsaj:" << (hasViolated ? "DA" : "NE") << std::endl
		<< std::setw(25) << std::left << "Cijena:" << price << " " << CURRENCY << std::endl;

	printReceiptHeader(str);
}
