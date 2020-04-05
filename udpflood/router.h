#ifndef _ROUTER_H_
#define _ROUTER_H_

#include "Node.h"
#include "Common.h"
#include "Time.h"
#include "Logger.h"
#include "Core.h"

using namespace HSP_NS;

class Router : public Node{
public:
    Router(NODE_ID nodeId)
        : Node(nodeId)
    {}
    virtual int receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv){
        //转发
        int re = forward(pktRecv);
        if(re < 0)
            mark_to_drop(fromLink, pktRecv);
        return 0;
    }
private:
    int forward(shared_ptr<Packet> pktRecv){
        shared_ptr<Link> outLink = route(pktRecv->getDstIpAddr());
        if(outLink == nullptr)
            return -1;
        #ifdef NS3_CORE
        WRITE_LOG(INFO, "[%.12fs] Router=%u(%s) Route a packet, src=%s, dst=%s.", 
                ns3::Simulator::Now().GetSeconds(),
                getNodeId(),
                getLocalAddress().getAddrStr().c_str(),
                pktRecv->getSrcIpAddrStr().c_str(), 
                pktRecv->getDstIpAddrStr().c_str());
 
        #elif defined HSP_CORE
        WRITE_LOG(INFO, "[%ss] Router=%u(%s) Route a packet, src=%s, dst=%s.", 
                Simulator::getTimestamp(getNodeId(), Second).c_str(),
                getNodeId(),
                getLocalAddress().getAddrStr().c_str(),
                pktRecv->getSrcIpAddrStr().c_str(), 
                pktRecv->getDstIpAddrStr().c_str());
        #else
        WRITE_LOG(INFO, "[%ss] Router=%u(%s) Route a packet, src=%s, dst=%s.", 
                Simulator::getTimestamp(Second).c_str(),
                getNodeId(),
                getLocalAddress().getAddrStr().c_str(),
                pktRecv->getSrcIpAddrStr().c_str(), 
                pktRecv->getDstIpAddrStr().c_str());            
        #endif
        /*
        * MAC地址的修改暂不实现
        */
        return sendToLink(pktRecv, outLink);
    }
    void mark_to_drop(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv){
        //向源发送一个ICMP通知
        shared_ptr<Packet> icmpReply = make_shared<Packet>(pktRecv->getDstIpAddr(), pktRecv->getSrcIpAddr(), 64, "ICMP:unreachable");
        sendToLink(icmpReply, fromLink);
    }
};

#endif