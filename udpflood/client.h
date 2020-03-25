#ifndef _UDPCLIENT_H_
#define _UDPCLIENT_H_

#include "Node.h"
#include "Common.h"
#include "Time.h"
#include "Logger.h"
#include "Simulator.h"
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
    void setStartTime(Time time){Simulator::schedule(getNodeId(), time, "start udp-client application",  &UdpClient::startEvent, this); };
    void setStopTime(Time time) {Simulator::schedule(getNodeId(), time, "stop udp-client application",  &UdpClient::stopEvent, this); };
public: //Event
    void startEvent(){
        _state = 1;
        Simulator::schedule(getNodeId(), Time(Second,0), "Send Begin.",  &UdpClient::sentOnePacket, this); 
    }
    void stopEvent(){
        _state = 0;
    }
    void sentOnePacket(){
        Ipv4Address localAddr = getLocalAddress();
        shared_ptr<Packet> pkt = make_shared<Packet>(localAddr,_dstAddr,_pktSize);
        sendDefault(pkt);
        WRITE_LOG(INFO, "[%ss] client=%u(%s) send one packet to %s.",
                        Simulator::getTimestamp(Second).c_str(),
                        getNodeId(),
                        getLocalAddress().getAddrStr().c_str(),
                        _dstAddr.getAddrStr().c_str());
        _hasSent += 1;
        if(_state == 1 && _hasSent < _pktNum){
            Simulator::schedule(getNodeId(), _ingerval, "Send Continue.",  &UdpClient::sentOnePacket, this); 
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