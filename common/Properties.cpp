#include "Properties.h"
#include "Constants.h"
#include "CsvParser.h"
#include <vector>

namespace Properties
{
	static unsigned int numNodes;
	static std::vector<std::string> vehicleCategories;
	static bool isLoaded = false;

	void load()
	{
		CsvParser csvParser;
		csvParser.open(FILE_GRAPH_DATA);

		// First cell MUST contain number of nodes.
		csvParser >> numNodes;

		// Rest of row is garbage. Next row is header.
		csvParser.goNextLine();

		// Skip 4 columns to get to categories.
		csvParser.goNextCol(4);

		// Load vehicle categories.
		while (!csvParser.currentLineEnded())
		{
			std::string vCategory;
			csvParser >> vCategory;
			vehicleCategories.push_back(vCategory);
			csvParser.goNextCol();
		}

		csvParser.close();

		isLoaded = true;
	}

	unsigned int getNumNodes()
	{
		if (!isLoaded) load();
		
		return numNodes;
	}

	const std::vector<std::string> &getVehicleCategories()
	{
		if (!isLoaded) load();

		return vehicleCategories;
	}
}