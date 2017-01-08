#pragma once
#include <string>
#include <tuple>
void generateConirmation(unsigned, std::string, std::string, std::string);
std::tuple<std::string, std::string, std::string, std::string, std::string> readConfirmation(unsigned);

bool confirmationExists(unsigned);