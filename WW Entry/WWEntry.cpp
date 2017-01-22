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

    entryNode = inputEntryNode();
    Console::clear();

	while(logUI.show())
    {

        logout = false;

        while (!logout)
        {

            int selection;
            printOptions();

            bool validSelection;

            std::cout << "Izaberi opciju: ";
            std::cin >> selection;

            validSelection = validateSelection(std::cin,selection);
            Console::resetStdin();
            Console::clear();

            if(!validSelection)
                std::cout << "Greska! Ta opcija ne postoji\n";

            else
                options[selection - 1].second();

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

	std::time_t time = std::time(NULL);
	std::string dateTime = TimeUtils::time2String(time, TIME_FORMAT);

	EntryCard confirmation(licensePlate, vehicleCategory, dateTime, entryNode);

	confirmation.writeToFile();

	Console::clear();

	std::cout << "Uspjesno generisan racun\n";

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
		Console::clear();

		if(!validCategory)
            std::cout << "Nepostojeca kategorija\n";

	}
	while (!validCategory);


	return category;

}


unsigned int WWEntry::inputEntryNode()
{

    unsigned int node;
    bool validNode;

    do
    {

        std::cout << "Ulazni cvor: ";
        std::cin >> node;

        validNode = Validation::isValidNode(node);
        Console::resetStdin();
        Console::clear();

        if(std::cin.fail() || !validNode)
            std::cout << "Nepostojeci ulazni cvor\n";

    }
    while(!validNode);

    return node;

}

