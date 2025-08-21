#include "point_provider.h"

int PointProvider::getPointPerDay(int dayIndex)
{
	return POINT_PER_DAY[dayIndex];
}

int PointProvider::getExtraPoint(int dayIndex)
{
	if (dayIndex == WEDNESDAY_INDEX) return ADDITIONAL_POINT_WED;
	else if (dayIndex == SATURDAY_INDEX || dayIndex == SUNDAY_INDEX) return ADDITIONAL_POINT_WEEKEND;
	return 0;
}