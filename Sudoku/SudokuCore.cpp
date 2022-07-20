#include "SudokuCore.h"
#include <iostream>
#include <fstream>
#include <QDebug>


// Default Constructor
SudokuCore::SudokuCore()
{
	// initialise grid to zeroes
	for (int r = 0; r < 9; r++)
	{
		std::vector<int> rowValues{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		gridValues.emplace_back(rowValues);
	}
}

// Default Destructor
SudokuCore::~SudokuCore()
{

}

// Load a game from file
bool SudokuCore::loadFromFile(std::string filePath)
{
	// open file
	std::fstream file;
	file.open(filePath, std::ios::in);
	
	// retrieve up to nine lines
	if (file.is_open())
	{
		
		for (int r = 0; r < 9; r++)
		{
			std::string line;

			// return false if early eof or line != 9 chars
			if (!getline(file, line))
			{
				file.close();
				return false;
			}

			if (line.size() != 9)
			{
				file.close();
				return false;
			}

			std::vector<int> rowValues;


			for (int c = 0; c < 9; c++)
			{
				char digit = line.at(c);

				if (!std::isdigit(digit))
				{
					file.close();
					return false;
				}

				rowValues.emplace_back(std::atoi(line.substr(c, 1).c_str()));
			}
						
			gridValues[r] = rowValues;
		}
	}

	// close file and return
	file.close();
	return true;
}

// Print current grid to console
void SudokuCore::print()
{
	for (std::vector<int> rowValues : gridValues)
	{
		for (int c : rowValues)
		{
			std::cout << c << " ";
			qDebug() << c;
		}

		std::cout << std::endl;
		qDebug() << "\n";
	}
}

// Solve puzzle (recursive strategy)
void SudokuCore::solve()
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (gridValues[r][c] != 0)
				continue;

			for (int candidate = 1; candidate < 10; candidate++)
			{
				if (isValid(r, c, candidate))
				{
					gridValues[r][c] = candidate;
					solve();
					gridValues[r][c] = 0;
				}
				return;
			}
		}
	}
}

int SudokuCore::getCellValue(int r, int c)
{
	return gridValues[r][c];
}


void SudokuCore::setCellValue(int r, int c, int value)
{
	gridValues[r][c] = value;
}

std::vector<int> SudokuCore::getRow(int r)
{
	return gridValues[r];
}

std::vector<int> SudokuCore::getColumn(int c)
{
	std::vector<int> columnValues;

	for (std::vector<int> rowValues : gridValues)
	{
		columnValues.emplace_back(rowValues[c]);
	}

	return columnValues;
}

std::vector<int> SudokuCore::getSubgrid(int r, int c)
{
	std::vector<int> subgridValues;

	// determine subgrid bounds
	int rowStart = (r % 3) * 3;
	int rowEnd = rowStart + 3;

	int columnStart = (c % 3) * 3;
	int columnEnd = columnStart + 3;

	for (int _r = rowStart; _r < rowEnd; _r++)
	{
		for (int _c = columnStart; _c < columnEnd; _c++)
		{
			subgridValues.emplace_back(gridValues[r][c]);
		}
	}

	return subgridValues;
}

// check if vector contains value
bool SudokuCore::contains(std::vector<int> v, int value)
{
	return std::find(v.begin(), v.end(), value) == v.end();
}

// Validity check
bool SudokuCore::isValid(int r, int c, int value)
{
	// if value is found in column, row or 3x3 subgrid, return false
	if (contains(getRow(r), value))
		return false;

	if (contains(getColumn(c), value))
		return false;

	if (contains(getSubgrid(r, c), value))
		return false;

	// otherwise
	return true;
}
