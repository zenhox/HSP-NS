#ifndef _NS3EVENTMANAGER_H_
#define _NS3EVENTMANAGER_H_

#include "Common.h"
#include "Event.h"
#include <map>
#include <memory>
using std::map;
using std::shared_ptr;
using std::pair;

namespace HSP_NS{

    // NS3 link map event manager
    class EventManager {
    private:
        map<EventKey, shared_ptr<EventHandler>> _eventMap;
        //Singleton
        EventManager()=default;
    public:
        static EventManager& getEventManager();
        // return 0: ok
        // return -1: no event to peek
        int peekNext(Event& ev);
        void insertEvent(const Event& event);
        void destroy();
    };
}


#endif