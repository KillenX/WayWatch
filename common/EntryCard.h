#pragma once
#include <string>
#include <ctime>

class EntryCard
{
public:
	EntryCard(const std::string = "", const std::string = "", const std::string = "", const int = -1);

	void readEntryCard(const std::string);

	void printEntryCardHeader(std::ostream &str);
	void printEntryCard(std::ostream &str);

	int getEntryTollbooth() const;
	std::string getVehicleCategory() const;
	std::string getDateTime() const;
	std::string getLicensePlate() const;

private:
	std::string vehicleCategory;
	std::string licensePlate;
	int entryTollbooth;
	std::string dateTime;
};

