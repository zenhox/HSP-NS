#include "Simulator.h"
#include "Network.h"
#include "server.h"
#include "client.h"
#include "Logger.h"
#include "router.h"
using namespace HSP_NS;

void p2r2pTest(){
    //生成2个node和link(delay,dataRate)                       目标服务器
    shared_ptr<UdpClient> client = make_shared<UdpClient>(1, "20.0.0.2", 2, 64, Time(MilliSecond, 1));
    shared_ptr<UdpServer> server = make_shared<UdpServer>(2, 64);
    shared_ptr<Router> router = make_shared<Router>(3);
    shared_ptr<Link> link_c2r = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  
    shared_ptr<Link> link_s2r = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

    //将client, router, server 连接:    c -- R -- s
    router->addLink(Ipv4Address("10.0.0.1"), link_c2r);
    client->addLink(Ipv4Address("10.0.0.2"), link_c2r);
    router->addLink(Ipv4Address("20.0.0.1"), link_s2r);
    server->addLink(Ipv4Address("20.0.0.2"), link_s2r);

    router->addRouteItem(Ipv4Address("10.0.0.2"), Ipv4Address("255.255.255.255"), link_c2r);
    router->addRouteItem(Ipv4Address("20.0.0.2"), Ipv4Address("255.255.255.255"), link_s2r);

    client->setStartTime(Time(Second, 1));
    client->setStopTime(Time(Second, 15));
    server->setStartTime(Time(Second, 1));
    server->setStopTime(Time(Second, 15));

    Simulator::run();
    Simulator::destroy();
}

void p2pTest(){
    //生成2个node和一个路由器
    shared_ptr<UdpClient> client = make_shared<UdpClient>(1, "20.0.0.1", 10, 64, Time(Second, 1));
    shared_ptr<UdpServer> server = make_shared<UdpServer>(2, 64);
    shared_ptr<Link> link = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

    //将n1,n2通过link连接
    client->addLink(Ipv4Address("10.0.0.1"), link);
    server->addLink(Ipv4Address("10.0.0.2"), link);

    client->setStartTime(Time(Second, 1));
    client->setStopTime(Time(Second, 15));
    server->setStartTime(Time(Second, 1));
    server->setStopTime(Time(Second, 15));

    Simulator::run();
    Simulator::destroy();  
}

int main(){
    Logger::initLogger("udpflood", "./log");
    p2r2pTest();
    return 0;
}