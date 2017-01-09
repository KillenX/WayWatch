#include "Receipt.h"
#include <iomanip>

Receipt::Receipt(std::string entryDate, int entryNode, 
	std::string exitDate, int exitNode, 
	std::string vCategory, double price, bool hasViolated,
	int receiptNumber)
	: entryDateTime(entryDate)
	, entryNode(entryNode)
	, exitDateTime(exitDate)
	, exitNode(exitNode)
	, vehicleCategory(vCategory)
	, price(price)
	, hasViolated(hasViolated)
	, receiptNumber(receiptNumber) {}

void Receipt::printReceiptHeader(std::ostream &str)
{
	str << "===================== ========== =================== ====== ================== ======= ================ ===========" << std::endl
		<< "   ENTRY DATE TIME     ENTRANCE    EXIT DATE TIME     EXIT   VEHICLE CATEGORY   PRICE   RECEIPT NUMBER   VIOLATION" << std::endl
		<< "===================== ========== =================== ====== ================== ======= ================ ===========" << std::endl;
}

void Receipt::printReceipt(std::ostream &str)
{
	str << " " << std::setw(21) << std::left << entryDateTime << "    " << std::setw(7) << std::left
		<< entryNode
		<< exitDateTime << "   " << std::setw(4) << std::left
		<< exitNode << "         " << std::setw(10) << std::left
		<< vehicleCategory << "   " << std::setw(5) << std::left
		<< price << "     " << std::setw(12) << std::left
		<< receiptNumber << "    "
		<< (hasViolated ? "YES" : "NO") << std::endl
		<< "===================== ========== =================== ====== ================== ======= ================ ===========" << std::endl;
}
