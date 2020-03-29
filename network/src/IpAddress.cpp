#include "IpAddress.h"
#include <arpa/inet.h>
#include <string.h>

namespace HSP_NS{

Ipv4Address::Ipv4Address(const String& addrStr){
    _addr = inet_addr(addrStr.c_str());
}
Ipv4Address::Ipv4Address(UINT32_T addrInt)
{
    _addr = addrInt;
}

Ipv4Address::Ipv4Address(const Ipv4Address& addr){
    _addr = addr._addr;
}

bool Ipv4Address::isValid()const{
    return _addr != INADDR_NONE;
}
String Ipv4Address::getAddrStr()const{
    if (_addr == INADDR_NONE)
        return String("<invalid addr>");
    struct in_addr addr;
    memcpy(&addr, &_addr, 4); 
    return String(inet_ntoa(addr));
}

UINT32_T Ipv4Address::getAddrVal()const{
    return _addr;
}

Ipv4Address Ipv4Address::mask(const Ipv4Address& mask)const{
    return Ipv4Address(_addr & mask._addr);
}
bool Ipv4Address::operator<(const Ipv4Address& another)const
{
    return _addr < another._addr;
}
bool Ipv4Address::operator!=(const Ipv4Address& another)const
{
    return _addr != another._addr;
}
bool Ipv4Address::operator==(const Ipv4Address& another)const
{
    return _addr == another._addr;
}

}