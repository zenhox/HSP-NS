#include "GridNode.h"
#include "Simulator.h"
#include <iostream>
#include <vector>
#include <memory>
#include <chrono> 
using namespace std;
using namespace HSP_NS;
using namespace chrono;


struct Args{
    int rowSize;
    int colSize;
    UINT32_T pktNum;
    UINT32_T pktSize;
    UINT32_T pktTTL;
    Time interval;
    Time startTime;
    Time endTime;
};

void test1(Args args);

UINT32_T THREAD_NUM = 2;
int main()
{
    Logger::initLogger("grid", "./log");
    Args args;
    // args.rowSize = 10;
    // args.colSize = 10;
    // args.pktNum = 30;
    // args.pktSize = 512;
    // args.pktTTL = 10;
    // args.interval = Time(MilliSecond,100);
    // args.startTime = Time(Second,1);
    // args.endTime = Time(Second,20);

    //DEBUG
    args.rowSize = 3;
    args.colSize = 3;
    args.pktNum = 1;
    args.pktSize = 512;
    args.pktTTL = 10;
    args.interval = Time(MilliSecond,100);
    args.startTime = Time(Second,1);
    args.endTime = Time(Second,20);

    #ifdef HSP_CORE
    Simulator::setSliceSize(Time(NanoSecond,900));
    #endif
    test1(args);
}


void test1(Args args){
    int rowSize = args.rowSize;
    int colSize = args.colSize;
    vector<vector<shared_ptr<GridNode>>> nodes(rowSize, vector<shared_ptr<GridNode>>(colSize, shared_ptr<GridNode>()));
    UINT32_T node_id = 1;
    for(int i=0; i<rowSize; ++i){
        for(int j=0; j<colSize; ++j){
            shared_ptr<GridNode> node = make_shared<GridNode>(node_id++, args.pktNum, args.pktSize * (i + j + 1), args.pktTTL, args.interval);
            node->setStartTime(args.startTime + Time(Second, i+j));
            node->setStopTime(args.endTime);
            node->setPos(i+1, j+1);
            nodes[i][j] = node;
        }
    }
    vector<shared_ptr<Link>> links;
    for(int i=0; i<rowSize; ++i){
        for(int j=0; j<colSize; ++j){
            if(i > 0){
                shared_ptr<Link> link = make_shared<Link>(Time(MicroSecond, 10), 100*1024*1024);
                nodes[i][j]->addLink(Ipv4Address("10."+to_string(i+1)+"."+to_string(j+1)+".1"), link);
                nodes[i-1][j]->addLink(Ipv4Address("10."+to_string(i+1)+"."+to_string(j+1)+".2"), link);
                links.push_back(link);
            }
            if(j > 0){
                shared_ptr<Link> link = make_shared<Link>(Time(MicroSecond, 10), 100*1024*1024);
                nodes[i][j]->addLink(Ipv4Address("20."+to_string(i+1)+"."+to_string(j+1)+".1"), link);
                nodes[i][j-1]->addLink(Ipv4Address("20."+to_string(i+1)+"."+to_string(j+1)+".2"), link);
                links.push_back(link);
            }
        }
    }
    auto start = system_clock::now();
    #ifdef NS3_CORE
    ns3::Simulator::Run();
    auto end   = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<<"Done. Cost real time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den  << " seconds."<<endl;
    cout<<"Total event : "<< ns3::Simulator::GetEventCount() <<endl;
    ns3::Simulator::Destroy();
    #elif defined HSP_CORE
    Simulator::run(THREAD_NUM);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<<"Done. Cost real time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den  << " seconds."<<endl;
    cout<<"Total event : "<< Simulator::getEventCount() <<endl;
    Simulator::destroy();
    #else
    Simulator::run();
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<<"Done. Cost real time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den  << " seconds."<<endl;
    cout<<"Total event : "<< Simulator::getEventCount() <<endl;
    cout<<"Min interval : "<< Simulator::_minInterval.getValue() <<endl;
    Simulator::destroy();
    #endif
}
