#include <iostream>
#include "Simulator.h"
#include <memory>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
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
    auto worker = g3::LogWorker::createLogWorker();
    auto handle= worker->addDefaultLogger("nstest", "./log");
    g3::initializeLogging(worker.get());
    A a;
    a.foo();
    Simulator::run();
    Simulator::destroy();
}
