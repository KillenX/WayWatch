#include "WWExit.h"
#include "Receipt.h"
#include "Ticket.h"
#include "../common/UserManager.h"
#include "../common/EntryCard.h"
#include "../common/TimeUtils.h"
#include "../common/Constants.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "../common/Console.h"
#include <limits>

static const int PENALTY = 100;

WWExit::WWExit() : programExit(false), graphHighway()
{
	initOptions();
}

void WWExit::run()
{
	tollBoothAmount = graphHighway.getNumNodes();

	inputTollBoothNumber();

	while (!programExit)
	{
		printOptions();

		int selection;
		std::cout << "Izaberite opciju: ";
		std::cin >> selection;
		Console::clear();

		if (validateSelection(std::cin, 1, options.size(), selection))
			options[selection - 1].second(); // menu options are [1...n], array is [0...n-1]
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
	Console::clear();

	EntryCard confirmation;

	if (confirmation.readEntryCard(DIR_ENTRY_CARDS + PREFIX_ENTRY_CARD + licensePlate + EXT_ENTRY_CARD) == false) // if Entry Card hasn't been found
	{
		std::cout << "Greska. Potvrda nije pronadjena." << std::endl;
		return;
	}

	std::time_t exitTime = std::time(NULL);
	std::string exitTimeString = TimeUtils::time2String(exitTime, TIME_FORMAT);

	// calculate toll and do speed control

	double toll = graphHighway.getToll(confirmation.getEntryTollbooth(), tollBoothNumber, confirmation.getVehicleCategory());

	double travelTime = difftime(exitTime, TimeUtils::string2Time(confirmation.getDateTime(), TIME_FORMAT)) / 60; // divide seconds by 60 to get in minutes

	bool hasViolated = graphHighway.hasViolatedSpeedLimit(confirmation.getEntryTollbooth(), tollBoothNumber, travelTime);

	Receipt receipt(confirmation.getDateTime(), confirmation.getEntryTollbooth(),
		exitTimeString, tollBoothNumber,
		confirmation.getVehicleCategory(), toll, hasViolated);

	receipt.printReceipt(std::cout);

	int choice;
	std::cout << "Racun je uspjesno generisan. " << std::endl << std::endl
			  << "1 - Izdaj racun." << std::endl
			  << "2 - Obrisi." << std::endl;

	std::cin >> choice;
	Console::clear();

	// TODO: make option selection a loop until right choice is made
	if (choice == 1)
	{
		std::string fileName = std::string(DIR_RECEIPTS + PREFIX_RECEIPT + confirmation.getLicensePlate() + EXT_RECEIPT);
		std::ofstream file(fileName, std::fstream::app);
		receipt.printReceipt(file);
		file.close();
		std::cout << "Racun uspjesno izdat. " << std::endl;

		if (hasViolated)
		{
			Ticket t(exitTimeString, licensePlate, PENALTY);

			std::string fileName = std::string(DIR_TICKETS + PREFIX_TICKET + licensePlate + EXT_TICKET);

			std::ofstream file(fileName, std::fstream::app);

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

bool WWExit::validateSelection(std::istream& str, int botLimit, int topLimit, int number)
{
	if (str.fail() || number < botLimit || number > topLimit)
	{
		str.clear();
		str.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skips
		return false;
	}
	return true;
}

void WWExit::inputTollBoothNumber()
{
	bool isValid = true;
	do
	{
		std::cout << "Unesite broj naplatne kucice: ";
		std::cin >> tollBoothNumber;

		if (validateSelection(std::cin, 1, tollBoothAmount, tollBoothNumber) == false)
{
			isValid = false;
			std::cout << "Greska. Ta naplatna kucica ne postoji." << std::endl;
		}
		else { isValid = true; }
		Console::clear();
	} while (isValid == false);
}

