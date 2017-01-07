#include "Receipt.h"
#include <iomanip>

Receipt::Receipt(std::string entryDate, int entryNode, 
	std::string exitDate, int exitNode, 
	std::string vCategory, double price, 
	bool hasViolated, int rNumber)
	: entryDateTime(entryDate)
	, entryNumber(entryNode)
	, exitDateTime(exitDate)
	, exitNumber(exitNode)
	, vehicleCategory(vCategory)
	, price(price)
	, receiptNumber(rNumber) {}

void Receipt::printReceiptHeader(std::ostream &str)
{
	str << "=========================== ========================= ================== ======= ================" << std::endl
		<< " ENTRY DATE TIME / NUMBER   EXIT DATE TIME / NUMBER     VEHICLE CATEGORY  PRICE   RECEIPT NUMBER" << std::endl
		<< "=========================== ========================= ================== ======= ================" << std::endl;
}

void Receipt::printReceipt(std::ostream &str)
{
	str << " " << entryDateTime << " / " << std::setw(6) << std::left
		<< entryNumber << " "
		<< exitDateTime << " / " << std::setw(9) << std::left
		<< exitNumber << "         " << std::setw(10) << std::left
		<< vehicleCategory << "  " << std::setw(4) << std::left
		<< price << "      "
		<< receiptNumber << std::endl
		<< "=========================== ========================= ================== ======= ================" << std::endl;
}
