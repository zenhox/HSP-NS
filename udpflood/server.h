#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include "Node.h"
#include "Common.h"
#include "Time.h"
#include "Logger.h"
#include "Core.h"

using namespace HSP_NS;

class UdpServer : public Node{
public:
    UdpServer(NODE_ID nodeId, UINT32_T replySize)
        : Node(nodeId)
    {
        _state = 0;
        _replySize = 64;
    }
    void setStartTime(Time time){
        #ifdef NS3_CORE
        ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &UdpServer::startEvent, this);
        #elif defined HSP_CORE
        Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "start udp-server application",  &UdpServer::startEvent, this); 
        #else
        Simulator::schedule(getNodeId(), time, "start udp-server application",  &UdpServer::startEvent, this); 
        #endif
    };
    void setStopTime(Time time) {
        #ifdef NS3_CORE
        ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &UdpServer::stopEvent, this);
        #elif defined HSP_CORE
        Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "stop udp-server application",  &UdpServer::stopEvent, this); 
        #else
        Simulator::schedule(getNodeId(), time, "stop udp-server application",  &UdpServer::stopEvent, this); 
        #endif
    };
    virtual int receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv){

        if(_state == 1) // running
        {
            shared_ptr<Packet> replyPkt = make_shared<Packet>(pktRecv->getDstIpAddr(), pktRecv->getSrcIpAddr(), _replySize, "I get your packet");
            #ifdef NS3_CORE
            WRITE_LOG(INFO, "[%.12fs] server=%u(%s) receive one packet from %s, reply it.",
                        ns3::Simulator::Now().GetSeconds(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        pktRecv->getSrcIpAddrStr().c_str());  
            #elif defined HSP_CORE
             WRITE_LOG(INFO, "[%ss] server=%u(%s) receive one packet from %s, reply it.",
                        Simulator::getTimestamp(getNodeId(), Second).c_str(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        pktRecv->getSrcIpAddrStr().c_str());           
            #else
            WRITE_LOG(INFO, "[%ss] server=%u(%s) receive one packet from %s, reply it.",
                        Simulator::getTimestamp(Second).c_str(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        pktRecv->getSrcIpAddrStr().c_str());
            #endif
            sendDefault(replyPkt); // 接收到就发送出去
            return 0;
        }
        return -1;
    }
public: //Event
    void startEvent(){
        _state = 1;
    }
    void stopEvent(){
        _state = 0;
    }
private:
    int _state;
    UINT32_T _replySize;
};

#endif