#include "WWExit.h"
#include "../common/UserManager.h"
#include "../common/Login.h"
#include <iostream>
#include <cstddef>


WWExit::WWExit() : programExit(false)
{
	initOptions();
}

void WWExit::run()
{
	bool loggedIn;
	UserManager users;
	
	do
	{
		auto credentials = Login::promptUser();
		loggedIn = users.login(credentials.first, credentials.second);

		if (!loggedIn)
			std::cout << "Netacno korisnicko ime/sifra\n";
	} while (!loggedIn);

	std::cout << "Uspjesno logovanje na sistem\n";

	while (!programExit)
	{
		printOptions();

		int selection;
		std::cin >> selection;
		selection--;//the options in menu are listed from 1 to n, options in array from 0 to n.

		if (validateSelection(std::cin, selection))
		{
			options[selection].second();
		}
		else
		{
			std::cout << "Greska. Ta opcija ne postoji." << std::endl;
		}
	}
}

void WWExit::printOptions()
{
	for (std::size_t index = 0; index < options.size(); ++index)
	{

		std::cout << index + 1 << ". " << options[index].first << std::endl;

	}
}

void WWExit::initOptions()
{
	options =
	{
		{ "Naplata putarine", std::bind(&WWExit::tollPayment, this) },

		{"Izlaz", std::bind(&WWExit::exit, this)},
	};
}

void WWExit::generateReceipt()
{

}

void WWExit::readEntryCard()
{
}

void WWExit::tollPayment()
{
	
}

void WWExit::exit()
{
	programExit = true;
}

bool WWExit::validateSelection(std::istream &stream, int selection)
{
	return !stream.fail() && selection >= 0 && selection < options.size();
}

