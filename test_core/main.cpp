#include <iostream>
#include "Simulator.h"
#include <memory>
#include "Logger.h"
#include <random>
using namespace::HSP_NS;

class A{
public:
    void foo(){
        Simulator::schedule(0, Time(Second,1), "测试event1", &A::event, this);
    }
    void event(){
        Simulator::schedule(1, Time(MilliSecond,100), "生成的event",  &A::newEvent, this, 3);
    }

    void newEvent(int a){
    }

};

void eventProcessDelay(Time time){
  clock_t start=clock();
  clock_t delay= static_cast<double>(time.getValue()) / 1000000000000 * CLOCKS_PER_SEC;
  while(clock()-start < delay);
}

void InternetStackProcessDelay(){
    eventProcessDelay(Time(MilliSecond, 1));
}
void ApplicationLaterProcessDelay()
{
    eventProcessDelay(Time(MilliSecond, 1));
}
void RandomDelay(Time begin, Time end){
    static thread_local std::random_device r;
    static thread_local std::mt19937 generator(r());
    std::uniform_int_distribution<UINT64_T> distribution(begin.getValue(),end.getValue());
    UINT64_T num = distribution(generator);
    Time delayTime =  Time(BaseTime, num);
    std::cout << num << endl;
    eventProcessDelay(delayTime);
}

int main(int argc, char **argv){
    // Logger::initLogger("nstest", "./log");
    // A a;
    // a.foo();
    // Simulator::run();
    // Simulator::destroy();
	RandomDelay(Time(Second,5),Time(Second,10));
}
