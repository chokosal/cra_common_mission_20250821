#include "gmock/gmock.h"
#include "data_parser.h"
#include "data_processor.h"

using namespace testing;

TEST(Parser, ReadOneRecord)
{
	DataParser parser;
	vector<attandanceRecordEntry> attandanceRecords{ 0 };

	string fileName = "TestInputRecord.txt";
	parser.addRecords(fileName, attandanceRecords);

	EXPECT_EQ(1, attandanceRecords.size());
}

TEST(Parser, Read500Record)
{
	DataParser parser;
	vector<attandanceRecordEntry> attandanceRecords{ 0 };

	string fileName = "attendance_weekday_500.txt";
	parser.addRecords(fileName, attandanceRecords);

	EXPECT_EQ(500, attandanceRecords.size());
}

TEST(Processor, HandleRecords)
{
	DataParser parser;
	vector<attandanceRecordEntry> attandanceRecords{ 0 };

	string fileName = "attendance_weekday_500.txt";
	parser.addRecords(fileName, attandanceRecords);

	DataProcessor processor;
	processor.HandleAttendanceRecords(attandanceRecords);

	EXPECT_EQ(500, attandanceRecords.size());
}