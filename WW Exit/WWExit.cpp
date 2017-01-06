#include "WWExit.h"
#include "../common/UserManager.h"
#include "../common/Login.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>


WWExit::WWExit(int tollBoothAmount) : programExit(false), tollBoothAmount(tollBoothAmount)
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
			std::cout << "Netacno korisnicko ime/sifra" << std::endl;
	} while (!loggedIn);

	std::cout << "Uspjesno logovanje na sistem." << std::endl << std::endl;

	do //Employee has to enter the number of the toll booth(tollBoothNumber) he's working in after he logs in.
	{
		std::cout << "Unesite broj naplatne kucice: " << std::endl;
		std::cin >> tollBoothNumber;
		//TODO: Safety check so it doesn't crash
	} while (tollBoothNumber < 1 || tollBoothNumber > tollBoothAmount);

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
	//eCard = readEntryCard(); //read Entry Card from a file
	
	Receipt rec("01.05.2016 00:00:05", 2, "01.5.2016 00:15:02",5,"D1A",25,125552); //TODO: replace with rec(eCard.entrydate, eCard.entryNumber ...
																				//TODO: make receipt counter
	rec.printReceiptHeader(std::cout); 
	rec.printReceipt(std::cout);

	int choice;
	std::cout << "Racun je uspjesno generisan. " << std::endl
		<< "1 - Izdaj racun." << std::endl
		<< "2 - Obrisi" << std::endl;

	std::cin >> choice;
	//TODO: safety check so it doesn't crash
	if (choice == 1)
	{
		std::ofstream file("Receipts.txt", std::fstream::app);

		rec.printReceiptHeader(file); //TODO: Make it such that header text gets printed only once to the file

		rec.printReceipt(file);

		file.close();

		std::cout << "Racun uspjesno izdat. " << std::endl;
	}
	else if (choice == 2)
	{
		std::cout << "Racun uspjesno obrisan. " << std::endl;
	}
	
}

void WWExit::exit()
{
	programExit = true;
}

bool WWExit::validateSelection(std::istream &stream, int selection)
{
	return !stream.fail() && selection >= 0 && selection < options.size();
}

WWExit::Receipt::Receipt(std::string entryDate, int entryNumber, std::string exitDate, int exitNumber, std::string vCategory, double price, int rNumber)
 : entryDateTime(entryDate), entryNumber(entryNumber), exitDateTime(exitDate), exitNumber(exitNumber), vehicleCategory(vCategory), price(price), receiptNumber(rNumber)
{
	
}

void WWExit::Receipt::printReceiptHeader(std::ostream &str)
{
	str << "=========================== ========================= ================== ======= ================" << std::endl
		<< " ENTRY DATE TIME / NUMBER   EXIT DATE TIME / NUMBER     VEHICLE CATEGORY  PRICE   RECEIPT NUMBER"  << std::endl
		<< "=========================== ========================= ================== ======= ================" << std::endl;
}

void WWExit::Receipt::printReceipt(std::ostream &str) 
{
	str << " " << entryDateTime << " / " << std::setw(4) << std::left
		<< entryNumber << " "
		<< exitDateTime << " / " << std::setw(4) << std::left
		<< exitNumber << "         " << std::setw(10) << std::left
		<< vehicleCategory << "  " << std::setw(4) << std::left
		<< price << "      "
		<< receiptNumber << std::endl
		<< "=========================== ========================= ================== ======= ================" << std::endl;
}
