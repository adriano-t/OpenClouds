#pragma once
#ifndef PACKET_H
#define PACKET_H

#include <cstdint>

namespace OpenClouds
{
	


	class Packet
	{

	};

	



	class PacketTime
	{
	public:

		int16_t year;
		int8_t month;
		int8_t day;
		int8_t hour;
		int8_t minute;
		int8_t second;


		PacketTime(int16_t year, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second)
		{
			this->year = year;
			this->month = month;
			this->day = day;
			this->hour = hour;
			this->minute = minute;
			this->second = second;
		}

		PacketTime() : year(year), month(month), day(day), hour(hour), minute(minute), second(second){
		}

		//check if the two dates are equal
		bool operator == (const PacketTime& pd) const
		{
			return(year == pd.year && month == pd.month && day == pd.day && hour == pd.hour && minute == pd.minute && second == pd.second);
		};

		//greater than operator
		bool operator > (const PacketTime& pd) const
		{
			if (year > pd.year)
				return true;
			else if(year == pd.year)
			{
				if ((month * 2592000 + day * 86400 + hour * 3600 + minute * 60 + second) > (pd.month * 2592000 + pd.day * 86400 + pd.hour * 3600 + pd.minute * 60 + pd.second))
					return true;
			}
			return false;
		};

		//less than operator
		bool operator < (const PacketTime& pd) const
		{
			if (year < pd.year)
				return true;
			else if (year == pd.year)
			{
				if ((month * 2592000 + day * 86400 + hour * 3600 + minute * 60 + second) < (pd.month * 2592000 + pd.day * 86400 + pd.hour * 3600 + pd.minute * 60 + pd.second))
					return true;
			}
			return false;
		};

	};


}

#endif