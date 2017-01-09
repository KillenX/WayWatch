#pragma once
#include <exception>
class InputConfirmationException : public std::exception
{
public:

	virtual const char* what() const;
	virtual ~InputConfirmationException();
};

