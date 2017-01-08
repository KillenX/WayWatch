#include "Confirmation.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "InputConfirmationException.h"
#include "OutputConfirmationException.h"
void generateConirmation(unsigned counter, std::string enterence, std::string category, std::string regiterPlates)
{
	auto t = std::time(nullptr); //current date&time
	auto tm = *std::localtime(&t);

	std::string number;
	std::ostringstream convert;
	convert << counter;
	number = convert.str();

	if (confirmationExists(counter))
	{
		InputConfirmationException exception;
		throw exception;
	}

	std::ofstream confirmation("confirmation" + number + ".txt", std::ios::out); //new confirmation made
	
	std::ostringstream date;
	std::ostringstream time;
	
	date << std::put_time(&tm, "%d-%m-%Y");
	time << std::put_time(&tm, "%H:%M:%S");

	confirmation << "========================================" << std::endl; //40 chars long
	confirmation << "Enterence:       " << enterence << std::endl; //17 chars long
	confirmation << "Date:            " << date.str() << std::endl;
	confirmation << "Time:            " << time.str() << std::endl;
	confirmation << "Category:        " << category << std::endl;
	confirmation << "Register plates: " << regiterPlates << std::endl;
	confirmation << "========================================" << std::endl;
	confirmation.close();
}

std::tuple<std::string, std::string, std::string, std::string> readConfirmation(unsigned ID)
{
	std::stringstream convert;
	convert << ID;

	std::ifstream confirmation("confirmation" + convert.str() + ".txt");
	if (!confirmation.is_open())
	{
		OutputConfirmationException exception;
		throw exception;
	}
	std::string enterence;
	std::string registrationPlates;
	std::string date;
	std::string time;
	std::string category;

	//Code that is heavily dependant on the look of the confirmationX.txt file
	confirmation.ignore(41, '\n');
	confirmation.ignore(17);
	std::getline(confirmation, enterence);
	confirmation.ignore(17);
	std::getline(confirmation, date);
	confirmation.ignore(17);
	std::getline(confirmation, time);
	confirmation.ignore(17);
	std::getline(confirmation, category);
	confirmation.ignore(17);
	std::getline(confirmation, registrationPlates);

	confirmation.close();
	
	return std::make_tuple < std::string, std::string, std::string, std::string, std::string>
		(enterence, date, time, category, registrationPlates);
}

bool confirmationExists(unsigned ID)
{
	std::string number;
	std::ostringstream convert;
	convert << ID;
	number = convert.str();

	std::ifstream confirmation("confirmation" + number + ".txt");
	return confirmation.is_open();
}