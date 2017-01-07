#include "WWExit.h"
#include "UserManager.h"
#include "Receipt.h"
#include "TimeUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

const char* TIME_FORMAT = "%d-%m-%y %H:%M:%S";

WWExit::WWExit() : programExit(false), graphHighway(FILE_ADJ_MATRIX)
{
	initOptions();
}

void WWExit::run()
{
	tollBoothAmount = graphHighway.getNumNodes();

	do 
	{
		std::cout << "Unesite broj naplatne kucice: " << std::endl;
		std::cin >> tollBoothNumber;
	} while (tollBoothNumber < 1 || tollBoothNumber > tollBoothAmount);

	while (!programExit)
	{
		printOptions();

		int selection;
		std::cin >> selection;
		selection--; // menu options are [1...n], array is [0...n-1]

		if (validateSelection(std::cin, selection))
			options[selection].second();
		else
			std::cout << "Greska. Ta opcija ne postoji." << std::endl;
	}
}

void WWExit::printOptions()
{
	for (std::size_t index = 0; index < options.size(); ++index)
		std::cout << index + 1 << ". " << options[index].first << std::endl;
}

void WWExit::initOptions()
{
	options =
	{
		{"Naplata putarine", std::bind(&WWExit::tollPayment, this) },
		{"Izlaz", std::bind(&WWExit::exit, this)},
	};
}

// TODO: move input queries to seperate function
void WWExit::tollPayment()
{
	// get exit time
	std::time_t exitTime = std::time(NULL);
	std::string exitDateTime = TimeUtils::Time2String(exitTime, TIME_FORMAT);
	
	// get entry time
	std::cout << "Unesite datum i vrijeme ulaska (DD-MM-YY HH:MM:SS): ";
	std::time_t entryTime = TimeUtils::StringStream2Time(std::cin, TIME_FORMAT);
	std::string entryDateTime = TimeUtils::Time2String(entryTime, TIME_FORMAT);

	// get entry node
	// TODO: input, range check;
	std::cout << "Unesite broj ulaznog cvora: ";
	int entryNode;
	std::cin >> entryNode;

	// get vehicle category
	// TODO: input check
	std::cout << "Unesite kategoriju vozila: ";
	std::string vehicleCategory;
	std::cin >> vehicleCategory;

	// calculate toll and do speed control
	double toll = graphHighway.getToll(entryNode, tollBoothNumber);
	double travelTime = (exitTime - entryTime) / 60; // divide seconds by 60 to get in minutes
	bool hasViolated = graphHighway.hasViolatedSpeedLimit(entryNode, tollBoothNumber, travelTime);

	// TODO: algorithm for receiptNumber
	int receiptNumber = 0;

	Receipt receipt(entryDateTime, entryNode, 
		exitDateTime, tollBoothNumber, 
		vehicleCategory, toll, hasViolated, 
		receiptNumber);

	receipt.printReceiptHeader(std::cout);
	receipt.printReceipt(std::cout);

	int choice;
	std::cout << "Racun je uspjesno generisan. " << std::endl
			  << "1 - Izdaj racun" << std::endl
			  << "2 - Obrisi" << std::endl;

	std::cin >> choice;

	// TODO: make option selection a loop until right choice is made
	if (choice == 1)
	{
		std::ofstream file("Receipts.txt", std::fstream::app);
		receipt.printReceiptHeader(file);
		receipt.printReceipt(file);
		file.close();
		std::cout << "Racun uspjesno izdat. " << std::endl;
	}

	if (choice == 2)
		std::cout << "Racun uspjesno obrisan. " << std::endl;

}

void WWExit::exit()
{
	programExit = true;
}

bool WWExit::validateSelection(std::istream &stream, int selection)
{
	return !stream.fail() && selection >= 0 && selection < options.size();
}