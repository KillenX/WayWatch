#include "Confirmation.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace EntryCardNS
{
	void printConfirmation(const unsigned counter, const int entryNode, const std::string vehicleCategory, const std::string registerPlates)
	{
		auto t = std::time(nullptr); // current date&time

		std::tm tm;
		localtime_s(&tm, &t);

		std::string number;
		std::ostringstream convert;
		convert << counter;
		number = convert.str();

		std::ofstream confirmation(ENTRY_CARD_FOLDER + "confirmation" + number + ".txt", std::ios::out); //new confirmation made

		std::ostringstream date;
		std::ostringstream time;

		date << std::put_time(&tm, "%d-%m-%Y");
		time << std::put_time(&tm, "%H:%M:%S");

		confirmation << "========================================" << std::endl; //40 chars long
		confirmation << "Entry node:       " << entryNode << std::endl; //17 chars long
		confirmation << "Date:            " << date.str() << std::endl;
		confirmation << "Time:            " << time.str() << std::endl;
		confirmation << "Category:        " << vehicleCategory << std::endl;
		confirmation << "Register plates: " << registerPlates << std::endl;
		confirmation << "========================================" << std::endl;
		confirmation.close();
	}

	EntryCard readConfirmation(const std::string& ID)
	{

		std::ifstream confirmation(ENTRY_CARD_FOLDER + "confirmation" + ID + ".txt");

		int entryNode;
		std::string registrationPlates;
		std::string date;
		std::string time;
		std::string category;

		// Code that is heavily dependant on the look of the confirmationX.txt file
		confirmation.ignore(41, '\n');
		confirmation.ignore(17);
		confirmation >> entryNode;
		confirmation.ignore(17);
		std::getline(confirmation, date);
		confirmation.ignore(17);
		std::getline(confirmation, time);
		confirmation.ignore(17);
		std::getline(confirmation, category);
		confirmation.ignore(17);
		std::getline(confirmation, registrationPlates);

		confirmation.close();

		return std::make_tuple(entryNode, date, time, category, registrationPlates);
	}

	bool confirmationExists(const std::string& ID)
	{
		std::string number;
		std::ostringstream convert;
		convert << ID;
		number = convert.str();

		std::ifstream confirmation(ENTRY_CARD_FOLDER + "confirmation" + ID + ".txt");
		return confirmation.is_open();
	}
}