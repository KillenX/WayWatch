#pragma once
#include <string>
#include <ctime>

namespace TimeUtils
{
	static const size_t TIME_STRING_MAX_LENGTH = 32;

	// TODO: Variable max length output?
	// Returns string with max length being TIME_STRING_MAX_LENGTH.
	std::string time2String(const std::time_t &time, const std::string &formatString);

	// Returns time from string containing formatted time (formatString being the format used).
	std::time_t string2Time(const std::string &string, const std::string &formatString);
}