#include "Node.h"
#include "Logger.h"
#include "Core.h"

namespace HSP_NS{

    RouteMatch::RouteMatch(const String& netAddr, const String& netMask)
        : _subnetAddr(netAddr),
        _subnetMask(netMask)
    {
        //empty body
    }
    RouteMatch::RouteMatch(const Ipv4Address& netAddr, const Ipv4Address& netMask)
        : _subnetAddr(netAddr),
        _subnetMask(netMask)
    {
        //empty body
    }

    Ipv4Address RouteMatch::getSubnetAddr()const{
        return _subnetAddr;
    }
    Ipv4Address RouteMatch::getSubnetMask()const{
        return _subnetMask;
    }

    bool RouteMatch::isMatch(const Ipv4Address& addr)const{
        return addr.mask(_subnetMask) == _subnetAddr;
    }

    Node::Node(NODE_ID id)
        :_defaultLink(nullptr)
    {
        _nodeId = id;
    }

    int Node::addLink(const Ipv4Address& addr, shared_ptr<Link> link){
        // 不能shared_ptr<Node>(this)
        if(link->connect(shared_from_this()) != 0)
            return -1;
        _linkAddrMap.insert(std::make_pair(link, addr));
        _defaultLink = link;
        return 0;
    }
    int Node::addRouteItem(const Ipv4Address& addr, const Ipv4Address& mask, shared_ptr<Link> link){
        _routeTable.insert(std::make_pair(RouteMatch(addr, mask), link));
        return 0;
    }
     /*Event*/
    int Node::sendToLink(shared_ptr<Packet> pktSend, shared_ptr<Link> toLink){
        return toLink->sendToDevice(shared_from_this(), pktSend);
    }

    int Node::sendDefault(shared_ptr<Packet> pktSend){
        return _defaultLink->sendToDevice(shared_from_this(), pktSend);
    }

    int Node::receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv){
        #ifndef NS3_CORE
        WRITE_LOG(INFO, "[%ss] NodeId=%u(%s), Receive a packet from %s, msg(%s).",
                    Simulator::getTimestamp(Second).c_str(),
                    _nodeId,
                    pktRecv->getDstIpAddrStr().c_str(),
                    pktRecv->getSrcIpAddrStr().c_str(),
                    pktRecv->getMessage().c_str());
        #else
        WRITE_LOG(INFO, "[%.12fs] NodeId=%u(%s), Receive a packet from %s, msg(%s).",
            ns3::Simulator::Now().GetSeconds(),
            _nodeId,
            pktRecv->getDstIpAddrStr().c_str(),
            pktRecv->getSrcIpAddrStr().c_str(),
            pktRecv->getMessage().c_str());
        #endif
        return 0;
    }

    shared_ptr<Link> Node::defaultRoute()const{
        return _defaultLink;
    }
    void Node::setDefaultRoute(shared_ptr<Link> link){
        _defaultLink = link;
    }

    shared_ptr<Link> Node::route(const Ipv4Address& dstAddr)const
    {
        if(_linkAddrMap.size() == 0)
        {
            return nullptr;
        }
        else if(_linkAddrMap.size() == 1)
        { //如果只有一个link, 说明是普通Node, 直接发出
            return _defaultLink;
        }
        else{
            for(auto& matchAction : _routeTable){
                    const RouteMatch& match = matchAction.first;
                    if(match.isMatch(dstAddr)){
                        return matchAction.second;
                    }
            }
            return nullptr;
        }
    }

    shared_ptr<Link> Node::route(const String& dstAddr)const
    {
        return route(Ipv4Address(dstAddr));
    }

    Ipv4Address Node::getLinkAddress(shared_ptr<Link> link)
    {
        return _linkAddrMap[link];
    }
    Ipv4Address Node::getLocalAddress()
    {
        return _linkAddrMap[_defaultLink];
    }
}