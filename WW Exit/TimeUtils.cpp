#include "TimeUtils.h"
#include <iomanip>

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

	std::time_t StringStream2Time(std::istream &istream, const char* formatString)
	{
		std::tm tm;

		memset(&tm, 0, sizeof(std::tm));
		istream >> std::get_time(&tm, formatString);

		return mktime(&tm);
	}
}