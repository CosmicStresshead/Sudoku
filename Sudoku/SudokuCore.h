#pragma once
#include <vector>
#include <string>

class SudokuCore
{
private:
	std::vector<std::vector<int>> gridValues;

public:
	SudokuCore();
	~SudokuCore();

	
	// File funcitons
	bool loadFromFile(std::string filePath);
	void print();
	void solve();

	// Accessors
	int getCellValue(int r, int c);
	void setCellValue(int r, int c, int value);

	std::vector<int> getRow(int r);
	std::vector<int> getColumn(int c);
	std::vector<int> getSubgrid(int r, int c);

	// Checking function
	bool isValid(int r, int c, int value);
	bool contains(std::vector<int> v, int value);
};