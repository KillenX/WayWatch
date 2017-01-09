#include "WWEntry.h"
#include "common/Login.h"
#include "common/UserManager.h"
#include "common/Console.h"
#include <iostream>
#include <cstddef>



WWEntry::WWEntry():programExit(false)
{

    initOptions();

}


void WWEntry::run()
{

    bool loggedIn;
    UserManager users;

    do
    {

        auto credentials = Login::promptUser();
        loggedIn = users.login(credentials.first,credentials.second);

        if(!loggedIn)
            std::cout << "Netacno korisnicko ime/sifra\n";

    }
    while(!loggedIn);

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
    std::string platesId;
    std::cin >> platesId;

    std::string vehicleCategory = inputCategory();

    // TODO:

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
    return !stream.fail() && selection >= 0 && selection < options.size();

}

std::string WWEntry::inputCategory()
{

    bool vehicleCategoryValid;

    do
    {

        std::cout << "Kategorija vozila: ";
        std::string vehicleCategory;
        std::cin >> vehicleCategory;

        vehicleCategoryValid; // TODO: Validate category input;

        if(!vehicleCategoryValid)
            std::cout << "Greska, kategorija nije validna\n";

    }
    while(!vehicleCategoryValid);

}
