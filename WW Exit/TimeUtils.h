#pragma once
#include <string>
#include <ctime>
#include <istream>

namespace TimeUtils
{
	std::string Time2String(const std::time_t &time, const char *formatString);
	std::time_t StringStream2Time(std::istream &is, const char *formatString);
}