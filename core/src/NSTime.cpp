#include "NSTime.h"
namespace HSP_NS{
Time::Time(){
    _timestamp = 0;
}
Time::Time(TIME_TYPE timeType, UINT64_T timeValue){
    if(timeType == NanoSecond){
        _timestamp = static_cast<UINT64_T>(timeValue);
    }else if(timeType == MicroSecond){
        _timestamp = static_cast<UINT64_T>(timeValue)*(1000);
    }
    else if(timeType == MilliSecond){
        _timestamp = static_cast<UINT64_T>(timeValue)*(1000000);
    }
    else if(timeType == Second){
        _timestamp = static_cast<UINT64_T>(timeValue)*(1000000000);
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
    return Time(NanoSecond, _timestamp + time2._timestamp);
}


}