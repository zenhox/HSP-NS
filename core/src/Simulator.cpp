#include "Simulator.h"

namespace HSP_NS{

Time Simulator::_curTime(Second,0); 

EventManager& Simulator::_eventManager = EventManager::getEventManager();
void Simulator::run(){
    Event nextEv = std::make_pair(EventKey(), nullptr);
    while(!_eventManager.peekNext(nextEv)){
        _curTime = (nextEv.first).getTimestamp();
        WRITE_LOG(DEBUG, "[%ss] Exec event, node=%u, event_id=%llu, description: %s", 
                    _curTime.toString(Second).c_str(), 
                    (nextEv.first).getNodeId(),
                    (nextEv.first).getEventId(),
                    (nextEv.first).getDescription().c_str());
        (nextEv.second)->invoke();
    }
}

void Simulator::destroy(){
    _eventManager.destroy();
    WRITE_LOG(DEBUG, "[%ss] Destroy the simulator", _curTime.toString(Second).c_str());
}

String Simulator::getTimestamp(TIME_TYPE type){
    return _curTime.toString(type);
}
UINT64_T Simulator::getEventCount(){
    return _eventManager.getEventCount();
}

}