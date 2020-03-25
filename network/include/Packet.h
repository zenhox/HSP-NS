#ifndef _NSPACKET_H_
#define _NSPACKET_H_

#include "Common.h"
#include "IpAddress.h"


namespace HSP_NS{

//精简化的数据包
class Packet{
public:
    Packet(const String& srcAddr, const String& dstAddr, UINT32_T pktSize, const String& msg="");
    Packet(const Ipv4Address& srcAddr, const Ipv4Address& dstAddr, UINT32_T pktSize, const String& msg="");
    Ipv4Address getDstIpAddr()const;
    Ipv4Address getSrcIpAddr()const;
    String getDstIpAddrStr()const;
    String getSrcIpAddrStr()const;
    UINT32_T getPktSize()const;
    String getMessage()const;
private:
    //暂时不写MAC地址
    Ipv4Address _ipv4Src;
    Ipv4Address _ipv4Dst;
    UINT32_T _pktSize;
    String _msg; 
};

}

#endif