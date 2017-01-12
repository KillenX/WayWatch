#include "WWEntry.h"
#include "../common/Constants.h"
#include "../common/Login.h"
#include "../common/UserManager.h"
#include "../common/Console.h"
#include "../common/EntryCard.h"
#include "../common/TimeUtils.h"
#include <iostream>
#include <cstddef>
#include <ctime>

using namespace WayWatch::Constants;

WWEntry::WWEntry():programExit(false)
{

    initOptions();

}


void WWEntry::run()
{

	Login::tryLogin();

    Console::clear();

    while (!programExit)
    {

        int selection;

        printOptions();
        std::cout << "\n";

        bool validSelection;

        do
		{
            std::cout << "Izaberi opciju: ";
            std::cin >> selection;

            validSelection = validateSelection(std::cin,selection);
            std::cin.clear();   // Recover if text is entered
            std::cin.ignore();  // Get rid of newline

            if(!validSelection)
                std::cout << "Greska!, opcija ne postoji\n";
        }
        while(!validSelection);

        Console::clear();
        options[selection - 1].second();
        Console::clear();

    }

}

void WWEntry::initOptions()
{

    options =
    {

        {"Izdavanje nove potvrde",std::bind(&WWEntry::generateEntryCard,this)},
        {"Izlaz",std::bind(&WWEntry::exit,this)}

	};

}

void WWEntry::generateEntryCard()
{

    std::cout << "Registarske tablice: ";
	std::string licensePlate;
    std::cin >> licensePlate;

    std::string vehicleCategory = inputCategory();

	int entryNode;
	std::cout << "Ulazni cvor: ";
	std::cin >> entryNode;

	//TODO: Validate entryNode

	std::time_t time = std::time(NULL);
	std::string dateTime = TimeUtils::time2String(time, TIME_FORMAT);

	EntryCard confirmation(licensePlate, vehicleCategory, dateTime, entryNode);

	confirmation.writeToFile();


}

void WWEntry::exit()
{

    programExit = true;

}

void WWEntry::printOptions()
{

    for(std::size_t index = 0; index < options.size(); ++index)
	{

        std::cout << index + 1 << ". " << options[index].first << "\n";

    }

}

bool WWEntry::validateSelection(std::istream &stream,int selection)
{

    --selection;
    // Casts to silence g++
    return !stream.fail() && static_cast<std::size_t>(selection) >= 0 &&
    static_cast<std::size_t>(selection) < options.size();

}

// TODO: check category valid
std::string WWEntry::inputCategory()
{

	std::cout << "Kategorija vozila: ";
	std::string vehicleCategory;
	std::cin >> vehicleCategory;
	return vehicleCategory;

}
