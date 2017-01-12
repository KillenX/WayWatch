#define _CRT_SECURE_NO_WARNINGS // std::localtime is not thread-safe
#include "TimeUtils.h"
#include <iomanip>
#include <sstream>
#include <limits>

namespace TimeUtils
{
	// TODO: Thread-safe alternative to std::localtime?
	std::string time2String(const std::time_t &time, const std::string &formatString)
	{
		char buff[TIME_STRING_MAX_LENGTH];
		std::strftime(buff, TIME_STRING_MAX_LENGTH, formatString.c_str(), std::localtime(&time));
		return std::string(buff);
	}

	// TODO: Check if the input string is actually formatted with respect to formatString?
	std::time_t string2Time(const std::string &string, const std::string &formatString)
	{
		std::tm tm;
		std::istringstream istringstream(string);
		std::memset(&tm, 0, sizeof(std::tm));
		istringstream >> std::get_time(&tm, formatString.c_str());

		return std::mktime(&tm);
	}
}
