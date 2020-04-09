#include "GridNode.h"
#include <memory>

namespace HSP_NS{
    class GridPacket : public Packet{
    public:
        GridPacket(const String& srcAddr, const String& dstAddr, UINT32_T pktSize, const String& msg="", UINT32_T ttl = 10)
            : Packet(srcAddr, dstAddr, pktSize, msg)
        {
            _TTL = ttl;
        }
        void setTTL(UINT32_T ttl){
            _TTL = ttl;
        }
        UINT32_T subTTL(){
            if(_TTL == 0)
                return 0;
            return --_TTL;
        }
    private:
        UINT32_T _TTL;
    };

    GridNode::GridNode(NODE_ID nodeId, UINT32_T pktNum, UINT32_T pktSize, UINT32_T pktTTL, Time interval)
        : Node(nodeId)
    {
         _state = 0;
         _pktNum = pktNum;
         _pktSize = pktSize;
         _pktTTL = pktTTL;
         _interval = interval;
         _hasSent = 0;
    }

    void GridNode::setStartTime(Time time)
    {
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &GridNode::startEvent, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "start grid node",  &GridNode::startEvent, this); 
        #else
            Simulator::schedule(getNodeId(), time, "start grid node",  &GridNode::startEvent, this);         
        #endif
    }
    void GridNode::setStopTime(Time time)
    {
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::PicoSeconds(time.getValue()), &GridNode::stopEvent, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), time), "stop grid node",  &GridNode::stopEvent, this); 
        #else
            Simulator::schedule(getNodeId(), time, "stop grid node",  &GridNode::stopEvent, this);      
        #endif
    }

    void GridNode::startEvent()
    {
        _state = 1;
        #ifdef NS3_CORE
            ns3::Simulator::Schedule(ns3::MilliSeconds(100), &GridNode::sentOnePacket, this);
        #elif defined HSP_CORE
            Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), Time(MilliSecond,100)), "Send Begin.",  &GridNode::sentOnePacket, this); 
        #else
            Simulator::schedule(getNodeId(), Time(MilliSecond,100), "Send Begin.",  &GridNode::sentOnePacket, this); 
        #endif
    }
    void GridNode::stopEvent()
    {
        _state = 0;
    }

    void GridNode::setPos(int x, int y){
        _posX = x;
        _posY = y;
    }

    int GridNode::receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv)
    {
        UINT32_T TTL = static_pointer_cast<GridPacket>(pktRecv)->subTTL();
        if(TTL == 0)
            return -1;

        #ifdef NS3_CORE
        WRITE_LOG(INFO, "[%.12fs] client=(%d,%d) receive a packet(TTL=%d), flooding...",
                        ns3::Simulator::Now().GetSeconds(),
                        _posX, _posY, TTL);
        #elif defined HSP_CORE
        WRITE_LOG(INFO, "[%ss] client=(%d,%d) receive a packet(TTL=%d), flooding...",
                        Simulator::getTimestamp(getNodeId(), Second).c_str(),
                        _posX, _posY, TTL);
        #else
        WRITE_LOG(INFO, "[%ss] client=(%d,%d) receive a packet(TTL=%d), flooding...",
                        Simulator::getTimestamp(Second).c_str(),
                        _posX, _posY, TTL);
        #endif
        
        String srcAddr = pktRecv->getSrcIpAddrStr();
        UINT32_T pktSize = pktRecv->getPktSize();
        String msg = pktRecv->getMessage();
        for(auto& link : _linkAddrMap){
            if(link.first != fromLink){
                std::shared_ptr<Packet> pkt = std::make_shared<GridPacket>(srcAddr, "255.255.255.255" , pktSize, msg, TTL);
                sendToLink(pkt, link.first);
            }
        }
        return 0;
    }

    void GridNode::sentOnePacket(){
        //每一个口都发一个TTL为
        //map<shared_ptr<Link>, Ipv4Address> _linkAddrMap;
        #ifdef NS3_CORE
        WRITE_LOG(INFO, "[%.12fs] client=(%d,%d) send a packet.",
                        ns3::Simulator::Now().GetSeconds(),
                        _posX, _posY);
        #elif defined HSP_CORE
        WRITE_LOG(INFO, "[%ss] client=(%d,%d) send a packet.",
                        Simulator::getTimestamp(getNodeId(), Second).c_str(),
                        _posX, _posY);
        #else
        WRITE_LOG(INFO, "[%ss] client=(%d,%d) send a packet.",
                        Simulator::getTimestamp(Second).c_str(),
                        _posX, _posY);
        #endif

        // for(int i=0; i<_linkAddrMap.size(); ++i){
        //     std::shared_ptr<Packet> pkt = std::make_shared<GridPacket>(_linkAddrMap[i].second.getAddrStr(), "255.255.255.255" ,_pktSize, "Flooding...", _TTL);
        //     sendToLink(pkt, _linkAddrMap[i].first);
        // }
        for(auto& link : _linkAddrMap){
            std::shared_ptr<Packet> pkt = std::make_shared<GridPacket>(link.second.getAddrStr(), "255.255.255.255" ,_pktSize, "Flooding...", _pktTTL);
            sendToLink(pkt, link.first);            
        }
        _hasSent += 1;
        if(_state == 1 && _hasSent < _pktNum){
            #ifdef NS3_CORE
                ns3::Simulator::Schedule(ns3::PicoSeconds(_interval.getValue()), &GridNode::sentOnePacket, this);
            #elif defined HSP_CORE
                Simulator::schedule(getNodeId(), Simulator::getTimestamp(getNodeId(), _interval), "Send Continue.",  &GridNode::sentOnePacket, this); 
            #else
                Simulator::schedule(getNodeId(), _interval, "Send Continue.",  &GridNode::sentOnePacket, this); 
            #endif           
        }
    }
}