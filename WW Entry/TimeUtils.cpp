#include "TimeUtils.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

namespace TimeUtils
{
	std::string Time2String(const std::time_t &time, const char* formatString)
	{
		std::tm tm;
		char buff[32];

		localtime_s(&tm, &time);
		strftime(buff, 32, formatString, &tm);

		return std::string(buff);
	}

	std::time_t String2Time(const std::string &string, const char* formatString)
	{
		std::tm tm;
		std::istringstream iss(string);
		memset(&tm, 0, sizeof(std::tm));
		iss >> std::get_time(&tm, formatString);

		return mktime(&tm);
	}
}