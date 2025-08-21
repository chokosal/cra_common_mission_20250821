#include "iostream"
#include "member.h"

using namespace std;

void MemberSheet::addMemberRecord(attandanceRecordEntry record)
{
	int id = allocateID(record.name);
	updatePerInputRecord(id, record.day);
}

void MemberSheet::wrapUpResult(void)
{
	addExtraPoint();
	giveGrade();
	printAttendanceResult();
}

int MemberSheet::allocateID(string name)
{
	if (userNameAndIdMap.count(name) == 0) {
		userNameAndIdMap.insert({ name, memberCount++ });
		memberInfo[userNameAndIdMap[name]].name = name;
	}
	return userNameAndIdMap[name];
}

void MemberSheet::updatePerInputRecord(int id, string day)
{
	int dayIndex = getDayIndex(day);
	updateAttandanceData(id, dayIndex);
}

int MemberSheet::getDayIndex(string day)
{
	if (day == MONDAY)  return MONDAY_INDEX;
	else if (day == TUESDAY) return TUESDAY_INDEX;
	else if (day == THURSDAY) return THURSDAY_INDEX;
	else if (day == FRIDAY) return FRIDAY_INDEX;
	else if (day == WEDNESDAY) return WEDNESDAY_INDEX;
	else if (day == SATURDAY) return SATURDAY_INDEX;
	return SUNDAY_INDEX;
}

void MemberSheet::updateAttandanceData(int attandanceID, int dayIndex)
{
	int add_point = pointQuery.getPointPerDay(dayIndex);

	//사용자ID별 요일 데이터에 1씩 증가
	memberInfo[attandanceID].attendanceCountPerDay[dayIndex]++;
	memberInfo[attandanceID].point += add_point;
}

void MemberSheet::addExtraPoint(void)
{
	for (int memberIndex = 0; memberIndex < memberCount; memberIndex++)
	{
		if (memberInfo[memberIndex].attendanceCountPerDay[WEDNESDAY_INDEX] >= DAY_NUM_FOR_WED)
		{
			memberInfo[memberIndex].point += pointQuery.getExtraPoint(WEDNESDAY_INDEX);
		}
	}

	for (int memberIndex = 0; memberIndex < memberCount; memberIndex++)
	{
		if (memberInfo[memberIndex].attendanceCountPerDay[SATURDAY_INDEX]
			+ memberInfo[memberIndex].attendanceCountPerDay[SUNDAY_INDEX] >= DAY_NUM_FOR_WEEKEND)
		{
			memberInfo[memberIndex].point += pointQuery.getExtraPoint(SUNDAY_INDEX);
		}
	}
}

void MemberSheet::giveGrade(void)
{
	for (int memberIndex = 0; memberIndex < memberCount; memberIndex++)
	{
		if (memberInfo[memberIndex].point >= POINT_FOR_GOLD) memberInfo[memberIndex].grade = GRADE_GOLD_VALUE;
		else if (memberInfo[memberIndex].point >= POINT_FOR_SILVER) memberInfo[memberIndex].grade = GRADE_SILVER_VALUE;
		else memberInfo[memberIndex].grade = GRADE_NORMAL_VALUE;
	}
}

void MemberSheet::printAttendanceResult(void)
{
	for (int memberIndex = 0; memberIndex < memberCount; memberIndex++)
	{
		cout << "NAME : " << memberInfo[memberIndex].name << ", ";
		cout << "POINT : " << memberInfo[memberIndex].point << ", ";
		cout << "GRADE : " << getGradeString(memberInfo[memberIndex].grade) << "\n";
	}

	printRemovedPlayers();
}

void MemberSheet::printRemovedPlayers()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int memberIndex = 0; memberIndex < memberCount; memberIndex++)
	{
		if (IsRemovalCondition(memberIndex)) {
			std::cout << memberInfo[memberIndex].name << "\n";
		}
	}
}

bool MemberSheet::IsRemovalCondition(int attandanceID)
{
	int countHardTrainingDay = getHardTraningDayJoinCount(attandanceID);

	if (memberInfo[attandanceID].grade != GRADE_NORMAL_VALUE) return false;
	else if (0 == countHardTrainingDay) return true;
	return false;
}

string MemberSheet::getGradeString(int grade)
{
	if (grade == GRADE_GOLD_VALUE) return GRADE_GOLD_STRING;
	else if (grade == GRADE_SILVER_VALUE) return GRADE_SILVER_STRING;
	return GRADE_NORMAL_STRING;
}

int MemberSheet::getHardTraningDayJoinCount(int attandanceID)
{
	int retCount = memberInfo[attandanceID].attendanceCountPerDay[WEDNESDAY_INDEX];
	retCount += memberInfo[attandanceID].attendanceCountPerDay[SATURDAY_INDEX];
	retCount += memberInfo[attandanceID].attendanceCountPerDay[SUNDAY_INDEX];

	return retCount;
}
