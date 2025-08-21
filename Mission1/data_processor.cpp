#include "data_processor.h"
#include <iostream>

void DataProcessor::HandleAttendanceRecords(vector<attandanceRecordEntry>& attandanceRecords)
{
	for (attandanceRecordEntry record : attandanceRecords)
	{
		memberSheet.addMemberRecord(record);
	}
	
	memberSheet.wrapUpResult();
}