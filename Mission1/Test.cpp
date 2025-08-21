#include "gmock/gmock.h"
#include "constants.h"
#include "test.h"
#include "data_parser.h"

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


TEST(PointProviderTest, getDayPoint)
{
	PointProvider pointQuery;
	int point = pointQuery.getPointPerDay(MONDAY_INDEX);
	EXPECT_EQ(POINT_NORMAL, point);

	point = pointQuery.getPointPerDay(TUESDAY_INDEX);
	EXPECT_EQ(POINT_NORMAL, point);

	point = pointQuery.getPointPerDay(WEDNESDAY_INDEX);
	EXPECT_EQ(POINT_WED, point);

	point = pointQuery.getPointPerDay(THURSDAY_INDEX);
	EXPECT_EQ(POINT_NORMAL, point);

	point = pointQuery.getPointPerDay(FRIDAY_INDEX);
	EXPECT_EQ(POINT_NORMAL, point);

	point = pointQuery.getPointPerDay(SATURDAY_INDEX);
	EXPECT_EQ(POINT_WEEKEND, point);

	point = pointQuery.getPointPerDay(SUNDAY_INDEX);
	EXPECT_EQ(POINT_WEEKEND, point);
}

TEST(PointProviderTest, getExtraPoint)
{
	PointProvider pointQuery;
	int point = pointQuery.getExtraPoint(WEDNESDAY_INDEX);
	EXPECT_EQ(ADDITIONAL_POINT_WED, point);

	point = pointQuery.getExtraPoint(SATURDAY_INDEX);
	EXPECT_EQ(ADDITIONAL_POINT_WEEKEND, point);

	point = pointQuery.getExtraPoint(MONDAY_INDEX);
	EXPECT_EQ(0, point);
}
