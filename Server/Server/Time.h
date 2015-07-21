#pragma once

#ifndef OC_TIME_H
#define OC_TIME_H

#include <cstdint>

namespace OpenClouds
{
	class Time
	{
	private:
		static const int64_t secsInMinute = 60;
		static const int64_t secsInHour = secsInMinute * 60;
		static const int64_t secsInDay = secsInHour * 24;
		static const int64_t secsInMonth = secsInDay * 31;
		static const int64_t secsInYear = secsInMonth * 12;

	public:
		int16_t year;
		int8_t month;
		int8_t day;
		int8_t hour;
		int8_t minutes;
		int8_t seconds;


		Time(int16_t year, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second)
		{
			this->year = year;
			this->month = month;
			this->day = day;
			this->hour = hour;
			this->minutes = minute;
			this->seconds = second;
		}

		Time() : year(year), month(0), day(0), hour(0), minutes(0), seconds(0)
		{
		}

		//check if the two dates are equal
		bool operator == (const Time& pd) const;

		//greater than operator
		bool operator > (const Time& pd) const;
		//less than operator
		bool operator < (const Time& pd) const;

		int64_t toInt64();
		void fromInt64(int64_t dateTime);
	};
}


#endif