#pragma once
#include <string>
#include <tuple>

const std::string ENTRY_CARD_FOLDER = "../data/entryCards/";
using EntryCard = std::tuple<int, std::string, std::string, std::string, std::string>;

namespace EntryCardNS
{
	void printEntryCard(const unsigned counter,
		const int entryNode,
		const std::string vehicleCategory,
		const std::string registerPlates);

	// entryNode, date, time, category, reg. plates
	EntryCard readEntryCard(const std::string& entryCardId);

	bool confirmationExists(const std::string& entryCardId);
}