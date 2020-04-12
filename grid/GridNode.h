#ifndef _GRIDNODE_H_
#define _GRIDNODE_H_

#include "Network.h"
#include "Simulator.h"
#include "Core.h"


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
    void writeLog();
private:
    int _state;
    UINT32_T _pktNum;
    UINT32_T _pktSize;
    UINT32_T _pktTTL;
    Time _interval;
    UINT32_T _hasSent;

    int _posX;
    int _posY;

    //** 用于验证正确性
    vector<String> _record;//第10, 100, 1000个包的信息
    int _recvCnt; //共接受多少个包
    UINT32_T _recvSize; //共接受多少字节
};


}


#endif