#include <iostream>
#include "Simulator.h"
#include <memory>
#include "Logger.h"
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

int main(int argc, char **argv){
    Logger::initLogger("nstest", "./log");
    A a;
    a.foo();
    Simulator::run();
    Simulator::destroy();
}
