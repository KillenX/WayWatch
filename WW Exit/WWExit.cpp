#include "WWExit.h"
#include "UserManager.h"
#include "Confirmation.h"
#include "Receipt.h"
#include "Ticket.h"
#include "TimeUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

const char* TIME_FORMAT = "%d-%m-%y %H:%M:%S";

WWExit::WWExit() : programExit(false), graphHighway()
{
	initOptions();
}

void WWExit::run()
{
	tollBoothAmount = graphHighway.getNumNodes();

	graphHighway.draw();

	do 
	{
		std::cout << "Unesite broj naplatne kucice: ";
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

void WWExit::printOptions() const
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
	std::string exitTimeString = TimeUtils::Time2String(exitTime, TIME_FORMAT);

	std::string entryCardId;
	std::cout << "Entry card number: ";
	std::cin >> entryCardId;

	EntryCard entryCard;
	entryCard = EntryCardNS::readConfirmation(entryCardId);

	int entryNode = std::get<0>(entryCard);
	std::string stringDate = std::get<1>(entryCard);
	std::string stringTime = std::get<2>(entryCard);
	std::string vehicleCategory = std::get<3>(entryCard);
	std::string stringPlates = std::get<4>(entryCard);

	std::string entryTimeString = stringDate + " " + stringTime;
	std::istringstream timeStream(entryTimeString);

	// get entry time
	std::cout << "Unesite datum i vrijeme ulaska (DD-MM-YY HH:MM:SS): ";
	std::time_t entryTime = TimeUtils::StringStream2Time(timeStream, TIME_FORMAT);
	// std::string entryDateTime = TimeUtils::Time2String(entryTime, TIME_FORMAT); wont need it as long as input gives correct time format??

	// calculate toll and do speed control
	double toll = graphHighway.getToll(entryNode, tollBoothNumber, vehicleCategory);
	double travelTime = difftime(exitTime, entryTime) / 60; // divide seconds by 60 to get in minutes
	bool hasViolated = graphHighway.hasViolatedSpeedLimit(entryNode, tollBoothNumber, travelTime);

	// TODO: algorithm for receiptNumber
	int receiptNumber = 1;

	Receipt receipt(entryTimeString, entryNode,
		exitTimeString, tollBoothNumber,
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
		std::string fileName = std::string("Receipts/Receipt") + std::to_string(receiptNumber) + std::string(".txt");
		std::ofstream file(fileName, std::fstream::app);
		receipt.printReceiptHeader(file);
		receipt.printReceipt(file);
		file.close();
		std::cout << "Racun uspjesno izdat. " << std::endl;

		if (hasViolated)
		{
			//TODO: replace "licensePlate" with EntryCard.licensePlate and 245 with actual ticket price
			Ticket t(exitTimeString, stringPlates, 245);

			// TODO: replace std::string("LicensePlate") with EntryCard.licensePlate
			std::string fileName = std::string("Tickets/Ticket") + stringPlates;

			std::ofstream file(fileName, std::fstream::app);
			t.printTicketHeader(file);
			t.printTicket(file);
		}
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