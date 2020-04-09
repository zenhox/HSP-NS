#ifndef _GRIDNODE_H_
#define _GRIDNODE_H_

#include "Network.h"
#include "Simulator.h"

namespace HSP_NS{


class GridNode : public Node{

public:
    GridNode(){};
    GridNode(NODE_ID nodeId, UINT32_T pktNum, UINT32_T pktSize, UINT32_T pktTTL, Time ingerval);
    void setStartTime(Time time);
    void setStopTime(Time time);
    virtual int receive(shared_ptr<Link> fromLink, shared_ptr<Packet> pktRecv);
    void setPos(int x, int y);
private:
    void startEvent();
    void stopEvent();
    void sentOnePacket();
private:
    int _state;
    UINT32_T _pktNum;
    UINT32_T _pktSize;
    UINT32_T _pktTTL;
    Time _interval;
    UINT32_T _hasSent;

    int _posX;
    int _posY;
};


}


#endif