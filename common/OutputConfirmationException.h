#pragma once
#include <exception>
class OutputConfirmationException : public std::exception
{
public:

	virtual const char* what() const;
	virtual ~OutputConfirmationException();
};

