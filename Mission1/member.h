#pragma once
#include <map>
#include <vector>
#include "constants.h"
#include "data_structure.h"
#include "point_provider.h"

using namespace std;

struct MemberInfo
{
	string name;
	int grade;
	int point;
	int attendanceCountPerDay[DAY_NUM];
};

class MemberSheet
{
public:
	void addMemberRecord(attandanceRecordEntry record);
	void wrapUpResult(void);

private:
	int allocateID(string name);
	void updatePerInputRecord(int index, string day);
	int getDayIndex(string day);
	void updateAttandanceData(int attandanceID, int dayIndex);
	void addExtraPoint(void);
	void giveGrade(void);
	void printAttendanceResult(void);
	void printRemovedPlayers(void);
	bool IsRemovalCondition(int attandanceID);
	string getGradeString(int grade);
	int getHardTraningDayJoinCount(int attandanceID);

	// name-id map
	map<string, int> userNameAndIdMap;
	// Memberinfo per id
	MemberInfo memberInfo[USER_NUM];
	PointProvider pointQuery;

	int memberCount = 0;
};