#include "Time.h"
#include <cstdint>

namespace OpenClouds
{

	bool Time::operator == (const Time& pd) const
	{
		return(year == pd.year && month == pd.month && day == pd.day && hour == pd.hour && minutes == pd.minutes && seconds == pd.seconds);
	};
	
	bool Time::operator > (const Time& pd) const
	{
		if (year > pd.year)
			return true;
		else if (year == pd.year)
		{
			if ((month * 2592000 + day * 86400 + hour * 3600 + minutes * 60 + seconds) > (pd.month * 2592000 + pd.day * 86400 + pd.hour * 3600 + pd.minutes * 60 + pd.seconds))
				return true;
		}
		return false;
	};

	bool Time::operator < (const Time& pd) const
	{
		if (year < pd.year)
			return true;
		else if (year == pd.year)
		{
			if ((month * 2592000 + day * 86400 + hour * 3600 + minutes * 60 + seconds) < (pd.month * 2592000 + pd.day * 86400 + pd.hour * 3600 + pd.minutes * 60 + pd.seconds))
				return true;
		}
		return false;
	};

	int64_t Time::toInt64()
	{
		// Seconds past from age 0.
		int64_t secondsCount = (int64_t)seconds + ((int64_t)minutes) * secsInMinute + ((int64_t)hour) * secsInHour +
			((int64_t)day) * secsInDay + ((int64_t)month) * secsInMonth + ((int64_t)year) * secsInYear;

		return(secondsCount);
	}

	void Time::fromInt64(int64_t dateTime)
	{
		year = 0;
		while (dateTime > secsInYear)
		{
			dateTime -= secsInYear;
			year++;
		}
		month = 0;
		while (dateTime > secsInMonth)
		{
			dateTime -= secsInMonth;
			month++;
		}
		day = 0;
		while (dateTime > secsInDay)
		{
			dateTime -= secsInDay;
			day++;
		}
		hour = 0;
		while (dateTime > secsInHour)
		{
			dateTime -= secsInHour;
			hour++;
		}
		minutes = 0;
		while (dateTime > secsInMinute)
		{
			dateTime -= secsInMinute;
			minutes++;
		}
		seconds = (int8_t)dateTime;
	}

}

