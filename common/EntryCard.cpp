#include "EntryCard.h"
#include "Constants.h"
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


bool EntryCard::readEntryCard(const std::string fileName)
{
	std::ifstream file(fileName);
	
	if (file.is_open() == false) return false; //if Entry Card hasn't been found

	std::string date;
	std::string time;

	file.ignore(100, '\n'); //skips header line "====..."
	file.ignore(100, ':');  //skips "Entry node:"

	file >> entryTollbooth;

	file.ignore(100, ':'); //skips "Date and Time:"

	file >> date;
	file >> time;

	file.ignore(100, ' '); //Skips "Category:"
	file >> vehicleCategory;

	file.ignore(100, ':'); //Skips "License plate:"
	file >> licensePlate;

	dateTime = date + " " + time;
	file.close();
	return true;
}


void EntryCard::printEntryCardHeader(std::ostream &str)
{
	str << "========================================" << std::endl;
}

void EntryCard::printEntryCard(std::ostream &str)
{
	str << "Entry node: " << entryTollbooth << std::endl
		<< "Date: " << dateTime << std::endl
		<< "Category: " << vehicleCategory << std::endl
		<< "License plate: " << licensePlate << std::endl
		<< "========================================" << std::endl;
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
    return std::string(DIR_ENTRY_CARDS + PREFIX_ENTRY_CARD + licensePlateID + EXT_ENTRY_CARD);
}


int EntryCard::getEntryTollbooth() const { return entryTollbooth; }

std::string EntryCard::getVehicleCategory() const { return vehicleCategory; }

std::string EntryCard::getDateTime() const { return dateTime; }

std::string EntryCard::getLicensePlate() const { return licensePlate; }
