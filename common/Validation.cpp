#include "Validation.h"
#include "Properties.h"
#include <algorithm>

namespace Validation
{
	bool isValidCategory(const std::string &category)
	{
		const std::vector<std::string> &vCategories = Properties::getVehicleCategories();
		if (std::find(vCategories.begin(), vCategories.end(), category) != vCategories.end())
			return true;

		return false;
	}

	bool isValidNode(const unsigned int node)
	{
		return (node != 0) && (node <= Properties::getNumNodes());
	}
}