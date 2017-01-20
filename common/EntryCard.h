#pragma once
#include <string>
#include <ctime>
#include <fstream>

class EntryCard
{

public:

	EntryCard(const std::string &licensePlate = "", const std::string &vehicleCategory = "",
           const std::string &dateTime = "", const int entryTollbooth = -1);

	bool readEntryCard(const std::string);

	void writeToFile();

	int getEntryTollbooth() const;
	std::string getVehicleCategory() const;
	std::string getDateTime() const;
	std::string getLicensePlate() const;



private:

    std::string generateFilename();
    void printEntryCardHeader(std::ostream &str);
	void printEntryCard(std::ostream &str);

	std::string vehicleCategory;
	std::string licensePlate;
	int entryTollbooth;
	std::string dateTime;
};

