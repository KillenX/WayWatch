#pragma once
#include <functional>
#include <vector>
#include <utility>
#include <string>

class WWExit
{
	struct Receipt
	{
			Receipt(std::string, int, std::string, int, std::string, double, int);
		public:
			std::string vehicleCategory;
			std::string entryDateTime;
			std::string exitDateTime;
		
			int entryNumber;
			int exitNumber;
			int receiptNumber;

			double price;
			
			void printReceiptHeader(std::ostream &str);
			void printReceipt(std::ostream &str);
	};

	bool programExit;
public:

	WWExit(int nodeNo);
	
	WWExit(const WWExit &) = delete;
	WWExit(WWExit &&) = delete;
	WWExit &operator=(const WWExit &) = delete;
	WWExit &operator=(WWExit &&) = delete;

	void run();

private:

	void printOptions();
	void initOptions();

	void generateReceipt();
	void readEntryCard();
	void tollPayment();
	void exit();

	bool validateSelection(std::istream &str, int selection);

	using Function= std::function <void()>;
	using Option = std::pair <std::string, Function>;

	std::vector <Option> options;

	int tollBoothNumber;
	int tollBoothAmount; //the amount of toll booths on the highway
};

