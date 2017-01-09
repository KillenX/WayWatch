#pragma once
#include <string>
#include <ctime>

namespace TimeUtils
{
	std::string Time2String(const std::time_t &time, const char *formatString);
	std::time_t String2Time(std::string string, const char *formatString);
}