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

	file.ignore(100,'\n'); file.ignore(100,'\n'); file.ignore(100,'\n'); //Skips header

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

void EntryCard::writeToFile()
{

    std::string filename = generateFilename(licensePlate);

    std::ofstream file(filename);

    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    printEntryCardHeader(file);
    printEntryCard(file);

}

std::string EntryCard::generateFilename(const std::string &licensePlateID)
{

    return std::string("../data/Confirmations/") + std::string("Confirmation") + licensePlateID + ".txt";

}


int EntryCard::getEntryTollbooth() const { return entryTollbooth; }

std::string EntryCard::getVehicleCategory() const { return vehicleCategory; }

std::string EntryCard::getDateTime() const { return dateTime; }

std::string EntryCard::getLicensePlate() const { return licensePlate; }
