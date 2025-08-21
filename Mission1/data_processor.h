#pragma once
#include "member.h"
#include "data_parser.h"

class DataProcessor
{
public:
	DataProcessor(MemberSheet* member) : memberSheet(member) {};
	void HandleAttendanceRecords(vector<attandanceRecordEntry>& attandanceRecords);
private:
	MemberSheet* memberSheet;
};