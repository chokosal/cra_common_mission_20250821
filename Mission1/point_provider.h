#include "constants.h"

class PointProvider
{
public:
	int getPointPerDay(int dayIndex);
	int getExtraPoint(int dayIndex);

private:
	const int POINT_PER_DAY[DAY_NUM] = { POINT_NORMAL, POINT_NORMAL, POINT_WED,
							POINT_NORMAL, POINT_NORMAL, POINT_WEEKEND, POINT_WEEKEND };

};