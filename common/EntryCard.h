#pragma once
#include <string>
#include <ctime>
#include <fstream>

class EntryCard
{
public:
	EntryCard(const std::string = "", const std::string = "", const std::string = "", const int = -1);

	bool readEntryCard(const std::string);

	void writeToFile();

	int getEntryTollbooth() const;
	std::string getVehicleCategory() const;
	std::string getDateTime() const;
	std::string getLicensePlate() const;

	static std::string generateFilename(const std::string &licensePlateID);

private:

    void printEntryCardHeader(std::ostream &str);
	void printEntryCard(std::ostream &str);

	std::string vehicleCategory;
	std::string licensePlate;
	int entryTollbooth;
	std::string dateTime;
};

