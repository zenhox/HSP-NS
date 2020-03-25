#ifndef _LINK_H_
#define _LINK_H_

#include "Node.h"
#include <deque>
#include "Time.h"
#include "Packet.h"
#include "Common.h"
#include <memory>


namespace HSP_NS{

class Packet;
class Node;

enum DEVICE_STATE {IDLE, WORKING};

class Device{
public:
    Device()=default;
    void pushTxQueue(shared_ptr<Packet> pkt);
    shared_ptr<Packet> peekTxQueue();
    bool isTxEmpty()const;
    // void pushRxQueue(shared_ptr<Packet> pkt);
    // shared_ptr<Packet> peekRxQueue();
    void setTxState(DEVICE_STATE state);
    // void setRxState(DEVICE_STATE state);
    DEVICE_STATE getTxState()const;
    // DEVICE_STATE getRxState()const;
    // UINT32_T getRemainTxBuf()const;
    // UINT32_T getRemainRxBuf()const;
private:
    std::deque<shared_ptr<Packet>> _txQueue;
    // std::deque<shared_ptr<Packet>> _rxQueue; //暂时不需要rxqueue
    UINT32_T _txSize; 
    // UINT32_T _rxSize;
    DEVICE_STATE _txState;
    // DEVICE_STATE _rxState;
    // UINT32_T _txBufferRemain;
    // UINT32_T _rxBufferRemain;
};

class Link : public std::enable_shared_from_this<Link>{
public:
    Link( Time delay, UINT64_T dataRate );

    int connect(std::shared_ptr<Node> node);

    // 将数据包放入发送队列
    int sendToDevice(shared_ptr<Node> srcNode, shared_ptr<Packet> pkt);

    /* Event */
    void transmitStart(shared_ptr<Node> srcNode);

    /* Event  peekAnother pkt and start transmit */
    void transmitComplete(shared_ptr<Node> dstNode, shared_ptr<Packet> pkt);

private:
    shared_ptr<Node> getAnother(shared_ptr<Node> node)const
    {
        return node == _nodeL.first? _nodeR.first : _nodeL.first;
    }
    Device& getDevice(shared_ptr<Node> node){
        return node == _nodeL.first? _nodeL.second : _nodeR.second;
    }
    Time _delay;  // 传播延时
    UINT64_T _sendRate; // bit
    Time _interframeGap; //帧间隔
    std::pair<shared_ptr<Node>, Device> _nodeL;
    std::pair<shared_ptr<Node>, Device> _nodeR;
};



}

#endif 