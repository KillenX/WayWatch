#include "WWEntry.h"
#include "../common/Login.h"
#include "../common/UserManager.h"
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

    std::cout << "Uspjesno logovanje na sistem\n";

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
            std::cin.clear();
            std::cin.ignore();

            if(!validSelection)
                std::cout << "Greska!, opcija ne postoji\n";


        }
        while(!validSelection);


        options[selection - 1].second();

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

