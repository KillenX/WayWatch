#include "WWExit.h"
#include "UserManager.h"
#include "Receipt.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

WWExit::WWExit() : programExit(false), graphHighway(FILE_ADJ_MATRIX)
{
	initOptions();
}

void WWExit::run()
{
	tollBoothAmount = graphHighway.getNumNodes();

	// employee has to enter the number of the toll booth (tollBoothNumber) he's working in after he logs in.
	do 
	{
		std::cout << "Unesite broj naplatne kucice: " << std::endl;
		std::cin >> tollBoothNumber;
		// TODO: Safety check so it doesn't crash
	} while (tollBoothNumber < 1 || tollBoothNumber > tollBoothAmount);

	while (!programExit)
	{
		printOptions();

		int selection;
		std::cin >> selection;
		selection--; // the options in menu are listed from 1 to n, options in array from 0 to n.

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

// TODO: M O D U L A R I Z E ! ! ! !
// MAKE CONVERSION ALGORITHMS BETTER!
void WWExit::tollPayment()
{
	// set current time (time of exit)
	// TODO: make better algorithm plz
	std::time_t exitTime = std::time(NULL);
	std::string exitDateTime;
	// exitTime into formatted string exitDateTime
	{
		struct tm ptr;
		char buff[32];
		localtime_s(&ptr, &exitTime);
		strftime(buff, 32, "%d-%m-%y %H:%M:%S", &ptr);
		exitDateTime = buff;
	}

	// get entry time
	// TODO: input check
	std::time_t entryTime;
	std::string entryDateTime;
	{
		std::tm tm;
		memset(&tm, 0, sizeof(std::tm));
		std::cout << "Unesite datum i vrijeme ulaska (DD-MM-YY HH:MM:SS): ";
		std::cin >> std::get_time(&tm, "%d-%m-%y %H:%M:%S");
		entryTime = mktime(&tm);
	}

	// entryTime into formatted string entryDateTime
	{
		struct tm ptr;
		char buff[32];
		localtime_s(&ptr, &entryTime);
		strftime(buff, 32, "%d-%m-%y %H:%M:%S", &ptr);
		entryDateTime = buff;
	}

	// get entry node
	// TODO: input, range check;
	int entryNode;
	std::cout << "Unesite broj ulaznog cvora: ";
	std::cin >> entryNode;

	// get vehicle category
	// TODO: input check
	std::string vehicleCategory;
	std::cout << "Unesite kategoriju vozila: ";
	std::cin >> vehicleCategory;

	double toll = graphHighway.getToll(entryNode, tollBoothNumber);
	bool hasViolated = graphHighway.hasViolatedSpeedLimit(entryNode, tollBoothNumber, (exitTime - entryTime) / 60.0);

	// TODO: algorithm for receiptNumber
	int receiptNumber = 0;

	Receipt receipt(entryDateTime, entryNode, exitDateTime, tollBoothNumber, vehicleCategory, toll, hasViolated, receiptNumber);

	receipt.printReceiptHeader(std::cout);
	receipt.printReceipt(std::cout);

	int choice;
	std::cout << "Racun je uspjesno generisan. " << std::endl
		<< "1 - Izdaj racun." << std::endl
		<< "2 - Obrisi" << std::endl;

	std::cin >> choice;

	//TODO: safety check so it doesn't crash
	if (choice == 1)
	{
		std::ofstream file("Receipts.txt", std::fstream::app);
		// TODO: Make it such that header text gets printed only once to the file
		receipt.printReceiptHeader(file);
		receipt.printReceipt(file);
		file.close();
		std::cout << "Racun uspjesno izdat. " << std::endl;
	}
	else if (choice == 2)
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