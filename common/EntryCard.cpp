#include "EntryCard.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

EntryCard::EntryCard(const std::string licensePlate, const std::string vehicleCategory, const std::string dateTime, const int entryTollbooth)
	: licensePlate(licensePlate),
	vehicleCategory(vehicleCategory),
	dateTime(dateTime),
	entryTollbooth(entryTollbooth) {}


void EntryCard::readEntryCard(const std::string fileName)
{
	std::ifstream file(fileName);

	std::string header;

	file >> header >> header >> header  //Skips the header from a file
		>> header >> header >> header >> header >> header >> header >> header >> header >> header
		>> header >> header >> header;

	std::string date;
	std::string time;

	file >> date;
	file >> time;

	dateTime = date + " " + time;

	file >> entryTollbooth;
	file >> vehicleCategory;
	file >> licensePlate;

	file.close();
}


void EntryCard::printEntryCardHeader(std::ostream &str)
{
	str << "========================== ================== ===============" << std::endl
		<< " ENTRY DATE TIME / NUMBER   VEHICLE CATEGORY   LICENSE PLATE" << std::endl
		<< "========================== ================== ===============" << std::endl;
}

void EntryCard::printEntryCard(std::ostream &str)
{
	//TODO: fix formatting
	str << dateTime << " " << entryTollbooth << " " << vehicleCategory << " " << licensePlate << std::endl
		<< "========================== ================== ===============" << std::endl;
}

int EntryCard::getEntryTollbooth() const { return entryTollbooth; }

std::string EntryCard::getVehicleCategory() const { return vehicleCategory; }

std::string EntryCard::getDateTime() const { return dateTime; }

std::string EntryCard::getLicensePlate() const { return licensePlate; }
