#include "Ticket.h"
#include "../common/Constants.h"
#include <iomanip>

Ticket::Ticket(std::string dateTime, std::string licensePlate, double price)
	: dateTime(dateTime),
	  licensePlate(licensePlate),
	  price(price) {}


void Ticket::printTicketHeader(std::ostream &str)
{
	str << "===========================================" << std::endl;
}

void Ticket::printTicket(std::ostream &str)
{
	printTicketHeader(str);

	str << std::setw(24) << std::left << "Vrijeme:" << dateTime << std::endl;
	str << std::setw(24) << std::left << "Registarske tablice:" << licensePlate << std::endl;
	str << std::setw(24) << std::left << "Cijena:" << price << " " << CURRENCY << std::endl;

	printTicketHeader(str);
}
