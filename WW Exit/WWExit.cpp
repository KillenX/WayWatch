#include "WWExit.h"
#include "Receipt.h"
#include "Ticket.h"
#include "../common/UserManager.h"
#include "../common/EntryCard.h"
#include "../common/TimeUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

WWExit::WWExit() : programExit(false), graphHighway()
{
	initOptions();
}

void WWExit::run()
{
	tollBoothAmount = graphHighway.getNumNodes();

	//ggraphHighway.draw();

	do 
	{
		std::cout << "Unesite broj naplatne kucice: ";
		std::cin >> tollBoothNumber;
	} while (tollBoothNumber < 1 || tollBoothNumber > tollBoothAmount);

	while (!programExit)
	{
		printOptions();

		int selection;
		std::cout << "Izaberite opciju: ";
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
	std::cout << "Registarske tablice: ";
	std::string licensePlate;
	std::cin >> licensePlate;

	std::time_t exitTime = std::time(NULL);
	std::string exitTimeString = TimeUtils::Time2String(exitTime, TIME_FORMAT);

	EntryCard confirmation;
	confirmation.readEntryCard("../data/Confirmations/" + std::string("Confirmation") + licensePlate + ".txt");

	// calculate toll and do speed control
	double toll = graphHighway.getToll(confirmation.getEntryTollbooth(), tollBoothNumber, confirmation.getVehicleCategory());
	double travelTime = difftime(exitTime, TimeUtils::String2Time(confirmation.getDateTime(), TIME_FORMAT)) / 60; // divide seconds by 60 to get in minutes
	bool hasViolated = graphHighway.hasViolatedSpeedLimit(confirmation.getEntryTollbooth(), tollBoothNumber, travelTime);

	// TODO: algorithm for receiptNumber
	int receiptNumber = 1;

	Receipt receipt(confirmation.getDateTime(), confirmation.getEntryTollbooth(),
		exitTimeString, tollBoothNumber,
		confirmation.getVehicleCategory(), toll, hasViolated,
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
		std::string fileName = std::string("../data/Receipts/Receipt") + confirmation.getLicensePlate() + ".txt";
		std::ofstream file(fileName, std::fstream::app);
		receipt.printReceiptHeader(file);
		receipt.printReceipt(file);
		file.close();
		std::cout << "Racun uspjesno izdat. " << std::endl;

		if (hasViolated)
		{
			Ticket t(exitTimeString, licensePlate, 100);

			std::string fileName = std::string("Tickets/Ticket") + licensePlate;

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