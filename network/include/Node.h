#ifndef _NSNODE_H_
#define _NSNODE_H_

#include "DelayAdd.h"
#include "Link.h"
#include "Packet.h"
#include "Common.h"
#include "IpAddress.h"
#include <memory>
#include <map>
using std::map;
using std::shared_ptr;

namespace HSP_NS{

class Link;

class RouteMatch{
private:
    Ipv4Address _subnetAddr;
    Ipv4Address _subnetMask;
public:
    RouteMatch(const String& netAddr, const String& netMask);
    RouteMatch(const Ipv4Address& netAddr, const Ipv4Address& netMask);
    Ipv4Address getSubnetAddr()const;
    Ipv4Address getSubnetMask()const;

    // 用于路由匹配
    bool isMatch(const Ipv4Address& addr)const;
    
    bool operator<(const RouteMatch& another)const{
        if(_subnetAddr != another._subnetAddr)
            return _subnetAddr < another._subnetAddr;
        else if(_subnetMask != another._subnetMask)
            return _subnetMask < another._subnetMask;
        return false;
    }
};

class Node : public std::enable_shared_from_this<Node>{

public:
    Node(NODE_ID id=0);

    NODE_ID getNodeId()const{return _nodeId;}

    //给node增加一个接口, 包含接口id, 接口地址, 接口object
    int addLink(const Ipv4Address& addr, shared_ptr<Link> link);
    int addRouteItem(const Ipv4Address& addr, const Ipv4Address& mask, shared_ptr<Link> link);
    Ipv4Address getLocalAddress();
    Ipv4Address getLinkAddress(shared_ptr<Link> link);
    
    // return 0 发送成功
    // return -1 发送失败
    int sendToLink(shared_ptr<Packet> pktSend, shared_ptr<Link> toLink);
    int sendDefault(shared_ptr<Packet> pktSend); //使用默认路由

    int receiveBase(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv){
        AddDelay::InternetStackProcessDelay();
        return this->receive(fromLink, pktRecv);
    }

    // receive call_back
    // 接收数据包的事件, 参数就是收到的数据包
    // 默认不对数据包做任何处理, 特定应用可以重载这个函数.
    virtual int receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv);

    //默认路由
    shared_ptr<Link> defaultRoute()const;
    void setDefaultRoute(shared_ptr<Link> link);
    virtual shared_ptr<Link> route(const Ipv4Address& dstAddr)const;
    virtual shared_ptr<Link> route(const String& dstAddr)const;
protected:
    map<RouteMatch, shared_ptr<Link>> _routeTable;
    map<shared_ptr<Link>, Ipv4Address> _linkAddrMap;
private:
    NODE_ID _nodeId;
    shared_ptr<Link> _defaultLink;
};

}





#endif