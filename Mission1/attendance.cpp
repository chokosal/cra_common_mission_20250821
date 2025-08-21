#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "constants.h"

using namespace std;

struct Node {
	string w;
	string wk;
};

map<string, int> attandanceSheet;
int registerCount = 0;

//dat[사용자ID][요일]
int attandanceRecord[USER_NUM][DAY_NUM];
int attandancePoint[USER_NUM];
int grade[USER_NUM];
string names[USER_NUM];

int wed[USER_NUM];
int weeken[USER_NUM];

void readAttandanceData(void);
void parseData(string name, string day);
int getAttandanceID(string name);
void allocateID(string name);
int getDayIndex(string day);
void updateAttandanceData(int attandanceID, int dayIndex);

void addExtraPoint(void);
void addPointForWed(void);
void addPointForWeekend(void);
void giveGrade(void);
void printAttandanceResult(void);
void printRemovedPlayers(void);
bool IsRemovalCondition(int attandanceID);

const int POINT_PER_DAY[] = { POINT_NORMAL, POINT_NORMAL, POINT_WED, 
								POINT_NORMAL, POINT_NORMAL, POINT_WEEKEND, POINT_WEEKEND };

int main() {
	readAttandanceData();
	addExtraPoint();
	giveGrade();
	printAttandanceResult();
}

void readAttandanceData(void)
{
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int inputLine = 0; inputLine < INPUT_LINE_NUM; inputLine++) {
		string name, day;
		fin >> name >> day;
		parseData(name, day);
	}
}

void parseData(string name, string day) {

	int attandanceID = getAttandanceID(name);

	//디버깅용
	if (name == "Daisy") {
		int debug = 1;
	}

	int dayIndex = getDayIndex(day);

	updateAttandanceData(attandanceID, dayIndex);
}

int getAttandanceID(string name)
{
	allocateID(name);
	return attandanceSheet[name];
}

void allocateID(string name)
{
	if (attandanceSheet.count(name) == 0) {
		attandanceSheet.insert({ name, ++registerCount });

		if (name == "Daisy") {
			int debug = 1;
		}

		names[registerCount] = name;
	}
}

int getDayIndex(string day)
{
	if (day == MONDAY)  return MONDAY_INDEX;
	else if (day == TUESDAY) return TUESDAY_INDEX; 
	else if (day == THURSDAY) return THURSDAY_INDEX; 
	else if (day == FRIDAY) return FRIDAY_INDEX; 
	else if (day == WEDNESDAY) return WEDNESDAY_INDEX;
	else if (day == SATURDAY) return SATURDAY_INDEX; 
	return SUNDAY_INDEX;
}

void updateAttandanceData(int attandanceID, int dayIndex)
{
	int add_point = POINT_NORMAL;

	add_point = POINT_PER_DAY[dayIndex];

	if (dayIndex == WEDNESDAY_INDEX) wed[attandanceID]++;
	else if (dayIndex == SATURDAY_INDEX || dayIndex == SUNDAY_INDEX) weeken[attandanceID]++;

	//사용자ID별 요일 데이터에 1씩 증가
	attandanceRecord[attandanceID][dayIndex]++;
	attandancePoint[attandanceID] += add_point;
}

void addExtraPoint(void)
{
	addPointForWed();
	addPointForWeekend();
}

void addPointForWed(void) {
	for (int registerIndex = 1; registerIndex <= registerCount; registerIndex++) {
		if (attandanceRecord[registerIndex][WEDNESDAY_INDEX] >= DAY_NUM_FOR_WED) {
			attandancePoint[registerIndex] += ADDITIONAL_POINT_WED;
		}
	}
}

void addPointForWeekend(void) {
	for (int registerIndex = 1; registerIndex <= registerCount; registerIndex++) {
		if (attandanceRecord[registerIndex][SATURDAY_INDEX] + attandanceRecord[registerIndex][SUNDAY_INDEX] >= DAY_NUM_FOR_WEEKEND) {
			attandancePoint[registerIndex] += ADDITIONAL_POINT_WEEKEND;
		}
	}
}

void giveGrade(void)
{
	for (int registerIndex = 1; registerIndex <= registerCount; registerIndex++) {
		if (attandancePoint[registerIndex] >= POINT_FOR_GOLD) grade[registerIndex] = GRADE_GOLD_VALUE;
		else if (attandancePoint[registerIndex] >= POINT_FOR_SILVER) grade[registerIndex] = GRADE_SILVER_VALUE;
		else grade[registerIndex] = GRADE_NORMAL_VALUE;
	}
}

void printAttandanceResult(void)
{
	for (int registerIndex = 1; registerIndex <= registerCount; registerIndex++)
	{
		cout << "NAME : " << names[registerIndex] << ", ";
		cout << "POINT : " << attandancePoint[registerIndex] << ", ";
		cout << "GRADE : ";

		if (grade[registerIndex] == GRADE_GOLD_VALUE) cout << GRADE_GOLD_STRING << "\n";	
		else if (grade[registerIndex] == GRADE_SILVER_VALUE) cout << GRADE_SILVER_STRING << "\n";
		else cout << GRADE_NORMAL_STRING << "\n";
	}

	printRemovedPlayers();
}

void printRemovedPlayers(void)
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int registerIndex = 1; registerIndex <= registerCount; registerIndex++) {
		if (IsRemovalCondition(registerIndex)) {
			std::cout << names[registerIndex] << "\n";
		}
	}
}

bool IsRemovalCondition(int attandanceID)
{
	if (grade[attandanceID] != GRADE_NORMAL_VALUE) return false;
	else if (wed[attandanceID] + weeken[attandanceID] == 0) return true;
	return false;
}