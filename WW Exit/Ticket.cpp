#include "Ticket.h"
#include <iomanip>

Ticket::Ticket(std::string dateTime, std::string licensePlate, double price)
	: dateTime(dateTime),
	  licensePlate(licensePlate),
	  price(price) {}


void Ticket::printTicketHeader(std::ostream &str)
{
	str << "===================================" << std::endl;
}

void Ticket::printTicket(std::ostream &str)
{
	printTicketHeader(str);

	str << std::setw(20) << std::left << "Date and time: " << dateTime;
	str << std::setw(20) << std::left << "License plate: " << licensePlate;
	str << std::setw(20) << std::left << "Price: " << price;

	printTicketHeader(str);
}
