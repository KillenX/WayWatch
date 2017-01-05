#pragma once
#include <functional>
#include <vector>
#include <utility>
#include <string>

class WWExit
{
	bool programExit;
public:

	WWExit();
	
	WWExit(const WWExit &) = delete;
	WWExit(WWExit &&) = delete;
	WWExit &operator=(const WWExit &) = delete;
	WWExit &operator=(WWExit &&) = delete;

	void run();

private:

	void printOptions();
	void initOptions();

	void generateReceipt();
	void readEntryCard();
	void tollPayment();
	void exit();

	bool validateSelection(std::istream &str, int selection);

	using Function= std::function <void()>;
	using Option = std::pair <std::string, Function>;

	std::vector <Option> options;
};

