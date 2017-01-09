#pragma once
#include <string>
#include <iostream>

class Ticket
{
public:
	Ticket(std::string, std::string, double);

	void printTicketHeader(std::ostream &);
	void printTicket(std::ostream &);
private:
	std::string licensePlate;
	std::string dateTime;
	double price;
};

