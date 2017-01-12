#pragma once
#include <string>

namespace WayWatch
{
	namespace Constants
	{
		// directories
		static const std::string DIR_DATA = "data/";
		static const std::string DIR_ENTRY_CARDS = DIR_DATA + "entry cards/";
		static const std::string DIR_RECEIPTS = DIR_DATA + "receipts/";
		static const std::string DIR_TICKETS = DIR_DATA + "tickets/";

		// extensions
		static const std::string EXT_ENTRY_CARD = ".txt";
		static const std::string EXT_RECEIPT = ".txt";
		static const std::string EXT_TICKET = ".txt";

		// file locations
		static const std::string FILE_EDGE_DATA = DIR_DATA + "EdgeData.csv";
		static const std::string FILE_DATABASE = DIR_DATA + "database.txt";

		// string formats
		static const std::string TIME_FORMAT = "%d-%m-%Y %H:%M:%S";
	}
}