#include "Simulator.h"
#include "Network.h"
#include "server.h"
#include "client.h"
#include "Logger.h"
#include "router.h"
#include <vector>
#include <ctime>
#include <iostream>
using namespace std;
using namespace HSP_NS;

struct Args{
    UINT32_T botNetNum;
    UINT32_T botPerNet;
    UINT32_T victimNum;
    UINT32_T pktNum;
    UINT32_T pktSize;
    Time interval;
    Time startTime;
    Time endTime;
};

void p2r2pTest();
void p2pTest();
void udpflood(Args args);


UINT32_T THREAD_NUM = 36;

int main(){
    Logger::initLogger("udpflood", "./log");
    Args args;
    args.botNetNum = 10;
    args.botPerNet = 10;
    args.victimNum = 5;
    args.pktNum = 100;
    args.pktSize = 64;
    args.interval = Time(MilliSecond,100);
    args.startTime = Time(Second,1);
    args.endTime = Time(Second,2000);


    // args.botNetNum = 1;
    // args.botPerNet = 1;
    // args.victimNum = 1;
    // args.pktNum = 10;
    // args.pktSize = 512;
    // args.interval = Time(MicroSecond,10);
    // args.startTime = Time(Second,1);
    // args.endTime = Time(Second,10);

    #ifdef HSP_CORE
    Simulator::setSliceSize(Time(NanoSecond,91));
    #endif

    udpflood(args);
    return 0;
}

void udpflood(Args args){
    UINT32_T node_id = 1;
    // 先创建核心的路由器
    shared_ptr<Router> coreRouter = make_shared<Router>(node_id++);
    // 创建受害者网络
    shared_ptr<Router> victimRouter = make_shared<Router>(node_id++);
    shared_ptr<Link> victimRouterLink = make_shared<Link>(Time(MicroSecond, 100), 1000*1024*1024);  //100us, 100G,, 这里无法描述 TODO
    coreRouter->addLink(Ipv4Address("20.0.0.1"), victimRouterLink);
    victimRouter->addLink(Ipv4Address("20.0.0.2"), victimRouterLink);
    coreRouter->addRouteItem(Ipv4Address("20.0.0.0"), Ipv4Address("255.255.0.0"), victimRouterLink); //client to server 的路由
    victimRouter->addRouteItem(Ipv4Address("10.0.0.0"), Ipv4Address("255.0.0.0"), victimRouterLink); // server to router 的路由
    vector<shared_ptr<UdpServer>> victims;
    vector<shared_ptr<Link>> victimLinks;
    for(UINT32_T i=0; i<args.victimNum; ++i){ // 创建受害者网络
        shared_ptr<UdpServer> server = make_shared<UdpServer>(node_id++, 64);
        shared_ptr<Link> link = make_shared<Link>(Time(MicroSecond, 10), 100*1024*1024); //00us, 100G,, 这里无法描述 TODO
        victimRouter->addLink(Ipv4Address("20.0."+to_string(i+1)+".1"), link);
        server->addLink(Ipv4Address("20.0."+to_string(i+1)+".2"), link);
        victimRouter->addRouteItem(Ipv4Address("20.0."+to_string(i+1)+".2"), Ipv4Address("255.255.255.255"), link);
        server->setStartTime(args.startTime);
        server->setStopTime(args.endTime);
        victims.push_back(server);
        victimLinks.push_back(link);
    }
    vector<shared_ptr<Router> > botRouters;
    vector<shared_ptr<Link> >   botRouterLinks;
    vector<vector<shared_ptr<UdpClient> >> allBots;
    vector<vector<shared_ptr<Link> > > allBotLinks;
    for(UINT32_T i=0; i<args.botNetNum; ++i){
        shared_ptr<Router> botRouter = make_shared<Router>(node_id++);
        shared_ptr<Link> botRouterLink = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024); // 1 ms, 1000M
        vector<shared_ptr<UdpClient>> bots;
        vector<shared_ptr<Link>> links;
        coreRouter->addLink(Ipv4Address("10."+to_string(i+1)+".0.1"), botRouterLink);
        botRouter->addLink(Ipv4Address("10."+to_string(i+1)+".0.2"), botRouterLink);
        coreRouter->addRouteItem(Ipv4Address("10."+to_string(i+1)+".0.0"), Ipv4Address("255.255.0.0"), botRouterLink); //client to server 的路由
        botRouter->addRouteItem(Ipv4Address("20.0.0.0"), Ipv4Address("255.255.0.0"), botRouterLink); // server to router 的路由
        for(UINT32_T j=0; j<args.botPerNet; ++j){
            shared_ptr<UdpClient> client = make_shared<UdpClient>(node_id++, "20.0."+to_string(j%args.victimNum+1)+".2", args.pktNum, args.pktSize, args.interval);
            shared_ptr<Link> link = make_shared<Link>(Time(MicroSecond, 10), 100*1024*1024);  // 100M
            botRouter->addLink(Ipv4Address("10."+to_string(i+1)+"."+to_string(j+1)+".1"), link);
            client->addLink(Ipv4Address("10."+to_string(i+1)+"."+to_string(j+1)+".2"), link);
            botRouter->addRouteItem(Ipv4Address("10."+to_string(i+1)+"."+to_string(j+1)+".2"), Ipv4Address("255.255.255.255"), link);
            client->setStartTime(args.startTime);
            client->setStopTime(args.endTime);
            bots.push_back(client);
            links.push_back(link);
        }
        botRouters.push_back(botRouter);
        botRouterLinks.push_back(botRouterLink);
        allBots.push_back(bots);
        allBotLinks.push_back(links);
    }
    std::clock_t tBegin = std::clock();
    #ifdef NS3_CORE
    ns3::Simulator::Run();
    std::clock_t tEnd = std::clock();
    std::clock_t costTime = (tEnd - tBegin)/CLOCKS_PER_SEC;
    cout<<"Done. Cost real time: " << costTime << " seconds."<<endl;
    cout<<"Total event : "<< ns3::Simulator::GetEventCount() <<endl;
    ns3::Simulator::Destroy();
    #elif defined HSP_CORE
    Simulator::run(THREAD_NUM);
    std::clock_t tEnd = std::clock();
    std::clock_t costTime = (tEnd - tBegin)/CLOCKS_PER_SEC;
    cout<<"Done. Cost real time: " << costTime << " seconds."<<endl;
    cout<<"Total event : "<< Simulator::getEventCount() <<endl;
    Simulator::destroy();
    #else
    Simulator::run();
    std::clock_t tEnd = std::clock();
    std::clock_t costTime = (tEnd - tBegin)/CLOCKS_PER_SEC;
    cout<<"Done. Cost real time: " << costTime << " seconds."<<endl;
    cout<<"Total event : "<< Simulator::getEventCount() <<endl;
    cout<<"Min interval : "<< Simulator::_minInterval.getValue() <<endl;
    Simulator::destroy();
    #endif
}

// void p2r2pTest(){
//     //生成2个node和link(delay,dataRate)                       目标服务器
//     shared_ptr<UdpClient> client = make_shared<UdpClient>(1, "20.0.0.2", 2, 64, Time(MilliSecond, 1));
//     shared_ptr<UdpServer> server = make_shared<UdpServer>(2, 64);
//     shared_ptr<Router> router = make_shared<Router>(3);
//     shared_ptr<Link> link_c2r = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  
//     shared_ptr<Link> link_s2r = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

//     //将client, router, server 连接:    c -- R -- s
//     router->addLink(Ipv4Address("10.0.0.1"), link_c2r);
//     client->addLink(Ipv4Address("10.0.0.2"), link_c2r);
//     router->addLink(Ipv4Address("20.0.0.1"), link_s2r);
//     server->addLink(Ipv4Address("20.0.0.2"), link_s2r);

//     router->addRouteItem(Ipv4Address("10.0.0.2"), Ipv4Address("255.255.255.255"), link_c2r);
//     router->addRouteItem(Ipv4Address("20.0.0.2"), Ipv4Address("255.255.255.255"), link_s2r);

//     client->setStartTime(Time(Second, 1));
//     client->setStopTime(Time(Second, 15));
//     server->setStartTime(Time(Second, 1));
//     server->setStopTime(Time(Second, 15));

//     #ifndef NS3_CORE 
//     // Simulator::run();
//     Simulator::destroy();
//     #else
//     // ns3::Simulator::Run();
//     ns3::Simulator::Destroy();
//     #endif
// }

// void p2pTest(){
//     //生成2个node和一个路由器
//     shared_ptr<UdpClient> client = make_shared<UdpClient>(1, "20.0.0.1", 10, 64, Time(Second, 1));
//     shared_ptr<UdpServer> server = make_shared<UdpServer>(2, 64);
//     shared_ptr<Link> link = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

//     //将n1,n2通过link连接
//     client->addLink(Ipv4Address("10.0.0.1"), link);
//     server->addLink(Ipv4Address("10.0.0.2"), link);

//     client->setStartTime(Time(Second, 1));
//     client->setStopTime(Time(Second, 15));
//     server->setStartTime(Time(Second, 1));
//     server->setStopTime(Time(Second, 15));

//     #ifndef NS3_CORE 
//     // Simulator::run();
//     Simulator::destroy();
//     #else
//     // ns3::Simulator::Run();
//     ns3::Simulator::Destroy();
//     #endif
// }
