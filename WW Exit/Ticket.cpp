#include "Ticket.h"

Ticket::Ticket(std::string dateTime, std::string licensePlate, double price)
	: dateTime(dateTime),
	  licensePlate(licensePlate),
	  price(price) {}


void Ticket::printTicketHeader(std::ostream &str)
{
	str << "============= =============== =======" << std::endl
	    << "  DATE TIME    LICENSE PLATE   PRICE"  << std::endl
		<< "============= =============== =======" << std::endl;
}

void Ticket::printTicket(std::ostream &str)
{
	//TODO: fix formatting
	str << dateTime << licensePlate << price << std::endl;
}
