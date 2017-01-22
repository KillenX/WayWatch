#include "WWEntry.h"
#include "../common/Constants.h"
#include "../common/Login.h"
#include "../common/UserManager.h"
#include "../common/Console.h"
#include "../common/EntryCard.h"
#include "../common/TimeUtils.h"
#include "../common/Validation.h"
#include <iostream>
#include <cstddef>
#include <ctime>

WWEntry::WWEntry():logout(false)
{

    initOptions();

}


void WWEntry::run()
{

	while(logUI.show())
    {

        while (!logout)
        {

            int selection;
            printOptions();

            bool validSelection;

            std::cout << "Izaberi opciju: ";
            std::cin >> selection;

            validSelection = validateSelection(std::cin,selection);
            std::cin.clear();   // Recover if text is entered
            std::cin.ignore();  // Get rid of newline
            Console::clear();

            if(!validSelection)
                std::cout << "Greska!, opcija ne postoji\n";

            else
            {

                options[selection - 1].second();
                Console::clear();

            }

        }

    }
}

void WWEntry::initOptions()
{

    options =
    {

        {"Izdavanje nove potvrde",std::bind(&WWEntry::generateEntryCard,this)},
        {"Odjava",std::bind(&WWEntry::logoutExit,this)}

	};

}

void WWEntry::generateEntryCard()
{

    std::cout << "Registarske tablice: ";
	std::string licensePlate;
    std::cin >> licensePlate;

    std::string vehicleCategory = inputCategory();
    unsigned int entryNode = inputEntryNode();

	std::time_t time = std::time(NULL);
	std::string dateTime = TimeUtils::time2String(time, TIME_FORMAT);

	EntryCard confirmation(licensePlate, vehicleCategory, dateTime, entryNode);

	confirmation.writeToFile();

}

void WWEntry::logoutExit()
{

    logout = true;

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


std::string WWEntry::inputCategory()
{

    std::string category;
    bool validCategory;

	do
	{

		std::cout << "Kategorija vozila: ";
		std::cin >> category;

		validCategory = Validation::isValidCategory(category);

		if(!validCategory)
            std::cout << "Nepostojeca kategorija\n";


	}
	while (!validCategory);


	return category;

}


unsigned int WWEntry::inputEntryNode()
{

    unsigned int entryNode;
    bool validNode;

    do
    {

        std::cout << "Ulazni cvor: ";
        std::cin >> entryNode;

        validNode = Validation::isValidNode(entryNode);

        if(!validNode)
            std::cout << "Nepostojeci ulazni cvor";

    }
    while(!validNode);

    return entryNode;

}
