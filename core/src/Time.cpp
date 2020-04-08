#include "Time.h"
#include <sstream>
#include <iomanip>

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
        _timestamp = static_cast<UINT64_T>(timeValue * SLICES_PER_NANOSE);
    }else if(timeType == MicroSecond){
        _timestamp = static_cast<UINT64_T>(timeValue * SLICES_PER_MICROS);
    }
    else if(timeType == MilliSecond){
        _timestamp = static_cast<UINT64_T>(timeValue * SLICES_PER_MILLIS);
    }
    else if(timeType == Second){
        _timestamp = static_cast<UINT64_T>(timeValue * SLICES_PER_SECOND);
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
Time Time::operator-(const Time& time2)const{
    return Time(BaseTime, _timestamp - time2._timestamp);
}

Time& Time::operator=(const Time& time2){
    _timestamp = time2._timestamp;
    return *this;
}

String Time::toString(TIME_TYPE timeType)const{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(12);
    switch(timeType){
        case Second:
            streamObj << static_cast<double>(_timestamp) / SLICES_PER_SECOND;
            break;
        case MilliSecond:
            streamObj << static_cast<double>(_timestamp) / SLICES_PER_MILLIS;
            break;
        case MicroSecond:
            streamObj << static_cast<double>(_timestamp) / SLICES_PER_MICROS;
            break;
        case NanoSecond:
            streamObj << static_cast<double>(_timestamp) / SLICES_PER_NANOSE;
            break;  
        case BaseTime:
            streamObj << static_cast<double>(_timestamp);
            break;
        default:
            break;                
    }
    return streamObj.str();
}

}