#include <iostream>
#include "Simulator.h"
#include "Network.h"
#include <memory>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
using namespace HSP_NS;
using namespace std;
using std::shared_ptr;

int main(int argc, char **argv){
    // 日志初始化
    auto worker = g3::LogWorker::createLogWorker();
    auto handle= worker->addDefaultLogger("network_test", "./log");
    g3::initializeLogging(worker.get());

    //生成2个node和link(delay,dataRate)
    shared_ptr<Node> n1 = make_shared<Node>(1);
    shared_ptr<Node> n2 = make_shared<Node>(2);
    shared_ptr<Link> link = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

    //将n1,n2通过link连接
    if(n1->addLink(0, Ipv4Address("10.0.0.1"), link) < 0)
        cout << "add link fail" <<endl;
    
    if(n2->addLink(0, Ipv4Address("10.0.0.2"), link) < 0)
        cout << "add link fail" <<endl;

    //给节点设置路由
    n1->addRouteItem(Ipv4Address("10.0.0.0"), Ipv4Address("255.255.255.0"), 0);
    n2->addRouteItem(Ipv4Address("10.0.0.0"), Ipv4Address("255.255.255.0"), 0);

    //生成一个从n1到n2的数据包
    shared_ptr<Packet> pkt = make_shared<Packet>("10.0.0.1", "10.0.0.2", 64);

    //插入事件: n1 在 1 second的时候，将 pkt 发送出去.
    Simulator::schedule(n1->getNodeId(), Time(Second,1), "Send packet",  &Node::send, n1, pkt);

    Simulator::run();
    Simulator::destroy();
}
