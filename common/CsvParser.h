#pragma once
#include <fstream>
#include <string>

static constexpr char CSV_DEFAULT_DELIMITER = ',';
static constexpr char NEWLINE_CHAR = '\n';

// Works for inputting from .csv only
// Explicit usage of methods required
class CsvParser
{
public:
	CsvParser();
	void open(const std::string& FileLocation);
	void close();
	bool currentCellEnded();
	bool currentLineEnded();
	bool reachedEOF();
	void goNextCol(unsigned n = 1); // moves forward by n cells
	void goNextLine(unsigned n = 1); // next row, first col
	template <typename T>
	friend CsvParser & operator>>(CsvParser &csvParser, T &dest); // reads from current cell
private:
	const char csvDelimiter = CSV_DEFAULT_DELIMITER;
	std::ifstream csv;
	bool isDelimiter(const char c) const;
};

template <typename T>
CsvParser & operator>>(CsvParser &csvParser, T &dest)
{
	if (!csvParser.currentCellEnded())
		csvParser.csv >> dest;

	return csvParser;
}

template <>
CsvParser & operator>><std::string>(CsvParser &csvParser, std::string &dest);

template <typename T>
CsvParser & operator>>(CsvParser &csvParser, T* &dest) = delete;