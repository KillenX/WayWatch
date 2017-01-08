#include "Confirmation.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>
void generateConirmation(unsigned counter, std::string enterence, std::string category, std::string regiterPlates)
{
	auto t = std::time(nullptr); //current date&time
	auto tm = *std::localtime(&t);

	std::string number;
	std::ostringstream convert;
	convert << counter;
	number = convert.str();

	std::ofstream confirmation("confirmation" + number + ".txt", std::ios::out); //new confirmation made

	std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << std::endl;
	
	std::ostringstream date;
	std::ostringstream time;
	
	date << std::put_time(&tm, "%d-%m-%Y");
	time << std::put_time(&tm, "%H:%M:%S");

	confirmation << "========================================" << std::endl; //40 chars long
	confirmation << "Enterence:       " << enterence << std::endl; //12 chars long
	confirmation << "Date:            " << date.str() << std::endl;
	confirmation << "Time:            " << time.str() << std::endl;
	confirmation << "Category:        " << category << std::endl;
	confirmation << "Register plates: " << regiterPlates << std::endl;
	confirmation << "========================================" << std::endl;
}
