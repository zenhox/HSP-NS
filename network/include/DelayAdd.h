#ifndef _DELAYADD_H_
#define _DELAYADD_H_

#include "Time.h"
#include <random>

namespace HSP_NS{

class AddDelay{
public:
    static void eventProcessDelay(Time time){
        clock_t start=clock();
        clock_t delay= static_cast<double>(time.getValue()) / 1000000000000 * CLOCKS_PER_SEC;
        while(clock()-start < delay);
    }

    static void InternetStackProcessDelay(){
        eventProcessDelay(Time(MilliSecond, 1));
    }
    static void ApplicationLaterProcessDelay()
    {
        eventProcessDelay(Time(MilliSecond, 1));
    }
    static void RandomDelay(Time begin, Time end){
        static thread_local std::random_device r;
        static thread_local std::mt19937 generator(r());
        std::uniform_int_distribution<UINT64_T> distribution(begin.getValue(),end.getValue());
        UINT64_T num = distribution(generator);
        Time delayTime =  Time(BaseTime, num);
        // std::cout << num << endl;
        eventProcessDelay(delayTime);
    }

};

}


#endif