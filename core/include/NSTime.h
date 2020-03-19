#ifndef _NSTIME_H_
#define _NSTIME_H_

#include "NSCommon.h"

namespace HSP_NS {
	class Time {
		private:
			UINT64_T _timestamp;
		public:
			Time();
			Time(TIME_TYPE timeType, UINT64_T timeValue);
			UINT64_T getValue()const;
			bool operator!=(const Time& time2)const;
			bool operator<(const Time& time2)const;
			Time operator+(const Time& time2)const;
	};
}
#endif