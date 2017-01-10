#pragma once
#include <string>
#include <ctime>

const std::string TIME_FORMAT = "%d-%m-%Y %H:%M:%S";

namespace TimeUtils
{
	std::string Time2String(const std::time_t &time, const std::string &formatString);
	std::time_t String2Time(const std::string &string, const std::string &formatString);
}