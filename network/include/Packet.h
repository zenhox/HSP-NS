#ifndef _NSPACKET_H_
#define _NSPACKET_H_

#include <string>
#include "Common.h"
#include "IpAddress.h"


namespace HSP_NS{

//精简化的数据包
class Packet{
public:
    Packet(const std::string& srcAddr, const std::string& dstAddr, UINT32_T pktSize);
    Packet(const Ipv4Address& srcAddr, const Ipv4Address& dstAddr, UINT32_T pktSize);
    Ipv4Address getDstIpAddr()const;
    Ipv4Address getSrcIpAddr()const;
    std::string getDstIpAddrStr()const;
    std::string getSrcIpAddrStr()const;
    UINT32_T getPktSize()const;
private:
    Ipv4Address _ipv4Src;
    Ipv4Address _ipv4Dst;
    UINT32_T _pktSize;
};

}

#endif