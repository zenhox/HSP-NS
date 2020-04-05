#ifndef _UDPCLIENT_H_
#define _UDPCLIENT_H_

#include "Node.h"
#include "Common.h"
#include "Time.h"
#include "Logger.h"
#include "Core.h"
using namespace HSP_NS;

class UdpClient : public Node{
public:
    UdpClient(NODE_ID nodeId, String dstAddr, UINT32_T pktNum, UINT32_T pktSize, Time ingerval)
        : Node(nodeId), _dstAddr(dstAddr)
    {
        _pktNum = pktNum;
        _pktSize = pktSize;
        _ingerval = ingerval;
        _hasSent = 0;
        _state = 0;
    }
    void setStartTime(Time time)
    {
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &UdpClient::startEvent, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "start udp-client application",  &UdpClient::startEvent, this); 
        #else
            Simulator::schedule(getNodeId(), time, "start udp-client application",  &UdpClient::startEvent, this);         
        #endif
    };
    void setStopTime(Time time)
    {
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &UdpClient::stopEvent, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "stop udp-client application",  &UdpClient::stopEvent, this); 
        #else
            Simulator::schedule(getNodeId(), time, "stop udp-client application",  &UdpClient::stopEvent, this);      
        #endif
    };
public: //Event
    void startEvent(){
        _state = 1;
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::Seconds(0), &UdpClient::sentOnePacket, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), Time(Second,0)), "Send Begin.",  &UdpClient::sentOnePacket, this); 
        #else
            Simulator::schedule(getNodeId(), Time(Second,0), "Send Begin.",  &UdpClient::sentOnePacket, this); 
        #endif
    }
    void stopEvent(){
        _state = 0;
    }
    void sentOnePacket(){
        Ipv4Address localAddr = getLocalAddress();
        shared_ptr<Packet> pkt = make_shared<Packet>(localAddr,_dstAddr,_pktSize);
        sendDefault(pkt);
        #ifdef NS3_CORE
        WRITE_LOG(INFO, "[%.12fs] client=%u(%s) send one packet to %s.",
                        ns3::Simulator::Now().GetSeconds(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        _dstAddr.getAddrStr().c_str());
        #elif defined HSP_CORE
        WRITE_LOG(INFO, "[%ss] client=%u(%s) send one packet to %s.",
                        Simulator::getTimestamp(getNodeId(), Second).c_str(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        _dstAddr.getAddrStr().c_str());
        #else
        WRITE_LOG(INFO, "[%ss] client=%u(%s) send one packet to %s.",
                        Simulator::getTimestamp(Second).c_str(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        _dstAddr.getAddrStr().c_str());
        #endif
        _hasSent += 1;
        if(_state == 1 && _hasSent < _pktNum){
            #ifdef NS3_CORE
                ns3::Simulator::Schedule(ns3::PicoSeconds(_ingerval.getValue()), &UdpClient::sentOnePacket, this);
            #elif defined HSP_CORE
                Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), _ingerval), "Send Continue.",  &UdpClient::sentOnePacket, this); 
            #else
                Simulator::schedule(getNodeId(), _ingerval, "Send Continue.",  &UdpClient::sentOnePacket, this); 
            #endif
        }
    }

    int _state;
    Ipv4Address _dstAddr;
    UINT32_T _pktNum;
    UINT32_T _pktSize;
    Time _ingerval;
    UINT32_T _hasSent;
};

#endif