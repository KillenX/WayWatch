#include "OutputConfirmationException.h"



const char * OutputConfirmationException::what() const
{
	return "Confirmation with that ID does not exist.\n";
}

OutputConfirmationException::~OutputConfirmationException() {}
