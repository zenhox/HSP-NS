#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include "Common.h"

namespace HSP_NS{
    
class Ipv4Address{
public:
    Ipv4Address(const Ipv4Address& addrStr);
    Ipv4Address(const String& addrStr);
    Ipv4Address(UINT32_T addrInt=-1);
    bool isValid()const;
    String getAddrStr()const;
    UINT32_T getAddrVal()const;
    Ipv4Address mask(const Ipv4Address& mask)const;
    bool operator<(const Ipv4Address& another)const;
    bool operator!=(const Ipv4Address& another)const;
    bool operator==(const Ipv4Address& another)const;
private:
    UINT32_T _addr;
};

}


#endif