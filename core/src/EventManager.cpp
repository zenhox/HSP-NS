#include "EventManager.h"


namespace HSP_NS{
    EventManager::EventManager(){
        _eventCount = 0;
    }
    EventManager& EventManager::getEventManager(){
        static EventManager singleton;
        return singleton;
    }

    void EventManager::insertEvent(const pair<EventKey, shared_ptr<EventHandler>>& event){
        _eventMap.insert(event);
        _eventCount += 1;
    }

    int EventManager::peekNext(Event& nextEv){
        if(_eventMap.begin() == _eventMap.end())
            return -1;
        auto i = _eventMap.begin ();
        nextEv = *i;
        _eventMap.erase (i);
        return 0;
    }

    void EventManager::destroy(){
        _eventMap.clear();
    }

    UINT64_T EventManager::getEventCount()const{
        return _eventCount;
    }
}