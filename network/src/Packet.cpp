#include "Packet.h"

namespace HSP_NS{
    Packet::Packet(const std::string& srcAddr, const std::string& dstAddr, UINT32_T pktSize)
        : _ipv4Src(srcAddr), _ipv4Dst(dstAddr), _pktSize(pktSize)
    {

    }
    Packet::Packet(const Ipv4Address& srcAddr, const Ipv4Address& dstAddr, UINT32_T pktSize)
        : _ipv4Src(srcAddr), _ipv4Dst(dstAddr), _pktSize(pktSize)
    {

    }

    Ipv4Address Packet::getDstIpAddr()const{
        return _ipv4Dst;
    }
    Ipv4Address Packet::getSrcIpAddr()const{
        return _ipv4Src;
    }

    std::string Packet::getDstIpAddrStr()const{
        return _ipv4Dst.getAddrStr();
    }
    std::string Packet::getSrcIpAddrStr()const{
        return _ipv4Src.getAddrStr();
    }
    UINT32_T Packet::getPktSize()const{
        return _pktSize;
    }
}