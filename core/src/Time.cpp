#include "Time.h"
namespace HSP_NS{
Time::Time(){
    _timestamp = 0;
}

Time::Time(const Time& time){
    _timestamp = time._timestamp;
}

Time::Time(TIME_TYPE timeType, double timeValue){
    if (timeType == BaseTime)
        _timestamp = static_cast<UINT64_T>(timeValue);
    else if(timeType == NanoSecond){
        _timestamp = static_cast<UINT64_T>(timeValue*1000);
    }else if(timeType == MicroSecond){
        _timestamp = static_cast<UINT64_T>(timeValue*1000000);
    }
    else if(timeType == MilliSecond){
        _timestamp = static_cast<UINT64_T>(timeValue*1000000000);
    }
    else if(timeType == Second){
        _timestamp = static_cast<UINT64_T>(timeValue*1000000000000);
    }
    else{
        _timestamp = 0;
    }
}
UINT64_T Time::getValue()const{
    return _timestamp;
}

bool Time::operator!=(const Time& time2)const{
    return _timestamp != time2._timestamp;
}

bool Time::operator<(const Time& time2)const{
    return _timestamp < time2._timestamp;
}

Time Time::operator+(const Time& time2)const{
    return Time(BaseTime, _timestamp + time2._timestamp);
}


}