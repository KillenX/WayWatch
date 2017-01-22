#include "EntryCard.h"
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

EntryCard::EntryCard(const std::string &licensePlate, const std::string &vehicleCategory, const std::string &dateTime, const int entryTollbooth)
	: vehicleCategory(vehicleCategory),
	licensePlate(licensePlate),
	entryTollbooth(entryTollbooth),
	dateTime(dateTime){}


bool EntryCard::readEntryCard(const std::string fileName)
{
	std::ifstream file(fileName);

	if (file.is_open() == false) return false; //if Entry Card hasn't been found

	std::string date;
	std::string time;

	file.ignore(100, '\n'); //skips header line "====..."
	file.ignore(100, ':');  //skips "Ulazni cvor:"

	file >> entryTollbooth;

	file.ignore(100, ':'); //skips "Vrijeme ulaza:"

	file >> date;
	file >> time;

	file.ignore(100, ':'); //skips "Kategorija vozila:"
	file >> vehicleCategory;

	file.ignore(100, ':'); //skips "Registarske tablice:"
	file >> licensePlate;

	dateTime = date + " " + time;
	file.close();
	return true;
}


void EntryCard::printEntryCardHeader(std::ostream &str)
{
	str << "=========================================" << std::endl;
}

void EntryCard::printEntryCard(std::ostream &str)
{
	printEntryCardHeader(str);

	str << std::setw(22) << std::left << "Ulazni cvor:" << entryTollbooth << std::endl
		<< std::setw(22) << std::left << "Vrijeme ulaza:" << dateTime << std::endl
		<< std::setw(22) << std::left << "Kategorija vozila:" << vehicleCategory << std::endl
		<< std::setw(22) << std::left << "Registarske tablice:" << licensePlate << std::endl;
	
	printEntryCardHeader(str);
}

void EntryCard::writeToFile()
{

    std::string filename = generateFilename();

    std::ofstream file(filename);

    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    printEntryCard(file);

}

std::string EntryCard::generateFilename()
{

    return std::string(DIR_ENTRY_CARDS + PREFIX_ENTRY_CARD + licensePlate + EXT_ENTRY_CARD);

}


int EntryCard::getEntryTollbooth() const { return entryTollbooth; }

std::string EntryCard::getVehicleCategory() const { return vehicleCategory; }

std::string EntryCard::getDateTime() const { return dateTime; }

std::string EntryCard::getLicensePlate() const { return licensePlate; }
