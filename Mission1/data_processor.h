#pragma once
#include "member.h"
#include "data_parser.h"

class DataProcessor
{
public:
	void HandleAttendanceRecords(vector<attandanceRecordEntry>& attandanceRecords);
private:
	MemberSheet memberSheet;
};