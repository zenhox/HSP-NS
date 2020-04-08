#ifndef _NSTIME_H_
#define _NSTIME_H_

#include "Common.h"



namespace HSP_NS {

	class Time {
		private:
			UINT64_T _timestamp;
		public:
			Time();
			Time(TIME_TYPE timeType, double timeValue);
			Time(const Time& time);
			UINT64_T getValue()const;
			String toString(TIME_TYPE timeType)const;

			Time& operator=(const Time& time2);

			bool operator!=(const Time& time2)const;
			bool operator<(const Time& time2)const;
			Time operator+(const Time& time2)const;
			Time operator-(const Time& time2)const;
	};
}
#endif