#include <iostream>
#include <fstream>
#include "data_parser.h"

void DataParser::addRecords(string fileName, vector<attandanceRecordEntry>& attandanceRecords)
{
	std::ifstream fin{ fileName }; //500개 데이터 입력

	for (int inputLine = 0; inputLine < INPUT_LINE_NUM; inputLine++) {
		attandanceRecordEntry recordEntry{ "", "" };
		fin >> recordEntry.name >> recordEntry.day;

		if (recordEntry.name == "" || recordEntry.day == "") 
		{
			break;
		}
			
		attandanceRecords.push_back(recordEntry);
	}
}
