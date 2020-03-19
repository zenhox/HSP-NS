#include <iostream>
#include "NS3Simulator.h"
#include <memory>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
using namespace::HSP_NS;

class A{
public:
    void foo(){
        Simulator::schedule(Time(Second,1), &A::event, this, "测试event1");
        Simulator::schedule(Time(Second,3), &A::event, this, "测试event2");
        Simulator::schedule(Time(Second,5), &A::event, this, "测试event3");
        Simulator::schedule(Time(Second,10), &A::event, this, "测试event4");
        Simulator::schedule(Time(Second,1000), &A::event, this, "测试event5");
    }
    void event(){
        Simulator::schedule(Time(MilliSecond,100), &A::newEvent, this, "生成的event");
    }

    void newEvent(){
    }

};

int main(int argc, char **argv){
    auto worker = g3::LogWorker::createLogWorker();
    auto handle= worker->addDefaultLogger("nstest", "./log");
    g3::initializeLogging(worker.get());
    A a;
    a.foo();
    Simulator::run();
    Simulator::destroy();
}
