#ifndef _NSNODE_H_
#define _NSNODE_H_

#include "Link.h"
#include "Packet.h"
#include "Common.h"
#include "IpAddress.h"
#include <memory>
#include <string>
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
    RouteMatch(const std::string& netAddr, const std::string& netMask);
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
    Node(NODE_ID id);

    NODE_ID getNodeId()const{return _nodeId;}

    //给node增加一个接口, 包含接口id, 接口地址, 接口object
    int addLink(UINT32_T id, const Ipv4Address& addr, shared_ptr<Link> link);
    int addRouteItem(const Ipv4Address& addr, const Ipv4Address& mask, UINT32_T linkId);

    // return 0 发送成功
    // return -1 发送失败
    int send(shared_ptr<Packet> pktSend);

    // receive call_back
    // 接收数据包的事件, 参数就是收到的数据包
    // 默认不对数据包做任何处理, 特定应用可以重载这个函数.
    virtual int receive(shared_ptr<Packet> pktRecv);

protected:
    //默认路由
    shared_ptr<Link> defaultRoute(const Ipv4Address& dstAddr)const;
private:
    NODE_ID _nodeId;
    map<UINT32_T, shared_ptr<Link>> _idLinkMap;
    map<Ipv4Address, shared_ptr<Link>> _addrLinkMap;
    map<RouteMatch, UINT32_T> _routeTable;
};

}





#endif