#include "Node.h"
#include <g3log/g3log.hpp>

namespace HSP_NS{

    RouteMatch::RouteMatch(const std::string& netAddr, const std::string& netMask)
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
    {
        _nodeId = id;
    }

    int Node::addLink(UINT32_T id, const Ipv4Address& addr, shared_ptr<Link> link){
        // 不能shared_ptr<Node>(this)
        if(link->connect(shared_from_this()) != 0)
            return -1;
        _addrLinkMap.insert(std::make_pair(addr, link));
        _idLinkMap.insert(std::make_pair(id, link));
        return 0;
    }
    int Node::addRouteItem(const Ipv4Address& addr, const Ipv4Address& mask, UINT32_T linkId){
        _routeTable.insert(std::make_pair(RouteMatch(addr, mask), linkId));
        return 0;
    }
     /*Event*/
    int Node::send(shared_ptr<Packet> pktSend){
        shared_ptr<Link> outIf = defaultRoute(pktSend->getDstIpAddr());
        //不能shared_ptr<Node>(this)
        return outIf->sendToDevice(shared_from_this(), pktSend);
    }

    int Node::receive(shared_ptr<Packet> pktRecv){
        // empty body.
        LOGF(INFO, "NodeId=%u(%s), Receive a packet from %s.",
                    _nodeId,
                    pktRecv->getDstIpAddrStr().c_str(),
                    pktRecv->getSrcIpAddrStr().c_str());
        return 0;
    }

    shared_ptr<Link> Node::defaultRoute(const Ipv4Address& dstAddr)const{
        for(auto& matchAction : _routeTable){
            const RouteMatch& match = matchAction.first;
            if(match.isMatch(dstAddr)){
                UINT32_T linkId = matchAction.second;
                auto it = _idLinkMap.find(linkId);
                if(it == _idLinkMap.end())
                {
                    LOGF(WARNING, "NodeId=%u(%s), Bad route item: subnet(%s) netmask(%s) linkId(%u).",
                                _nodeId,
                                match.getSubnetAddr().getAddrStr().c_str(),
                                match.getSubnetMask().getAddrStr().c_str(),
                                linkId);
                    return nullptr;
                }
                return it->second;
            }
        }
        return nullptr;
    }
}