#include "CsvParser.h"
#include <iostream>
#include <limits>

static const auto MAX_STREAM_SIZE = std::numeric_limits<std::streamsize>::max();

CsvParser::CsvParser() {}

void CsvParser::open(const std::string& FileLocation)
{
	csv.open(FileLocation);
}

void CsvParser::close()
{
	csv.close();
}

bool CsvParser::currentCellEnded()
{
	return isDelimiter(csv.peek());
}

bool CsvParser::currentLineEnded()
{
	char c = csv.peek();
	return (c == NEWLINE_CHAR) || (c == EOF);
}

bool CsvParser::reachedEOF()
{
	return csv.peek() == EOF;
}

void CsvParser::goNextCol(unsigned n)
{
	while (n-- && !currentLineEnded())
	{
		char c;

		do
		{
			c = csv.get();
		} while (!isDelimiter(c));
	}
}

void CsvParser::goNextLine(unsigned n)
{
	while (n-- && !reachedEOF())
		csv.ignore(MAX_STREAM_SIZE, NEWLINE_CHAR);
}

bool CsvParser::isDelimiter(const char c) const
{
	return (c == csvDelimiter) || (c == NEWLINE_CHAR) || (c == EOF);
}

template <>
CsvParser & operator>><std::string>(CsvParser &csvParser, std::string &dest)
{
	while (!csvParser.currentCellEnded())
		dest.push_back(csvParser.csv.get());

	return csvParser;
}
