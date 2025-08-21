#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "gmock/gmock.h"
#include "data_parser.h"
#include "data_processor.h"
#include "member.h"

using namespace std;

#ifdef _DEBUG
int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else

int main() {
	DataParser parser;
	vector<attandanceRecordEntry> attandanceRecords{ 0 };
	parser.addRecords("attendance_weekday_500.txt", attandanceRecords);
	
	DataProcessor processor;
	processor.HandleAttendanceRecords(attandanceRecords);
}
#endif
