#include "TimeUtils.h"
#include <iomanip>

namespace TimeUtils
{
	std::string Time2String(const std::time_t &time, const char* formatString)
	{
		std::string string;
		struct tm ptr;
		char buff[32];
		localtime_s(&ptr, &time);
		strftime(buff, 32, formatString, &ptr);
		string = buff;
		return string;
	}

	std::time_t StringStream2Time(std::istream &is, const char* formatString)
	{
		std::tm tm;
		memset(&tm, 0, sizeof(std::tm));
		is >> std::get_time(&tm, formatString);
		return mktime(&tm);
	}
}