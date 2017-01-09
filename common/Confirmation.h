#pragma once
#include <string>
#include <tuple>

const std::string ENTRY_CARD_FOLDER = "../data/entryCards/";

namespace Confirmation
{
	void printConfirmation(const unsigned counter,
		const int entryNode,
		const std::string vehicleCategory,
		const std::string registerPlates);

	// entryNode, date, time, category, reg. plates
	std::tuple<std::string, std::string, std::string, std::string, std::string> 
		readConfirmation(const std::string& entryCardId);

	bool confirmationExists(const std::string& entryCardId);
}