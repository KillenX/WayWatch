#include "InputConfirmationException.h"


const char * InputConfirmationException::what() const
{
	return "Confirmation with that ID already exists.\n";
}


InputConfirmationException::~InputConfirmationException()
{
}
