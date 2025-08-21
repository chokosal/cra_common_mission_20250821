#pragma once
#include <vector>
#include <string>
#include "constants.h"
#include "data_structure.h"

using std::string;
using std::vector;

class DataParser
{
public:
	DataParser(){}
	static void addRecords(string fileName, vector<attandanceRecordEntry>& attandanceRecords);
private:
};