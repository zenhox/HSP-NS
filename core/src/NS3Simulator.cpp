#include "NS3Simulator.h"
#include <g3log/g3log.hpp>

namespace HSP_NS{

Time Simulator::_curTime(Second,0); 
EventManager& Simulator::_eventManager = EventManager::getEventManager();
void Simulator::run(){
    Event nextEv = std::make_pair(EventKey(), nullptr);
    while(!_eventManager.peekNext(nextEv)){
        _curTime = (nextEv.first).getTimestamp();
        LOGF(DEBUG, "[%llu] Exec event, node=%u, event_id=%llu, description: %s", 
                    (nextEv.first).getTimestamp().getValue(), 
                    (nextEv.first).getNodeId(),
                    (nextEv.first).getEventId(),
                    (nextEv.first).getDescription().c_str());
        (nextEv.second)->invoke();
    }
}

void Simulator::destroy(){
    _eventManager.destroy();
}

}