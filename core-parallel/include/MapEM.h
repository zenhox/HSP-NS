#ifndef _NSEVENTMANAGER_H_
#define _NSEVENTMANAGER_H_

// lock free 数据结构
#include "sl_map.h"
#include "sl_set.h"

#include "Common.h"
#include "Event.h"

#include <memory>
#include <thread>
#include <atomic>
#include <iostream>
using namespace std;
using std::shared_ptr;


namespace HSP_NS{
    
    class SliceEvents{
    public:
        SliceEvents(UINT64_T id);
        ~SliceEvents();

        inline int insertEvent(const Event& event);

        UINT64_T getEventCount()const;
        UINT64_T getSliceId()const;
        sl_map_gc<NODE_ID, shared_ptr<sl_map_gc<EventKey, shared_ptr<EventHandler>>>> _sliceEvs;
    private:
        UINT64_T _sliceId;
        std::atomic<UINT64_T> _eventCnt;
    } ;

    // NS3 link map event manager
    class EventManager {
    public:
        static EventManager& getEventManager();
        int peekNextSlice(shared_ptr<SliceEvents> &sliceEvents);
        int insertEvent(const Event& event);
        UINT64_T getEventCount()const;
        void destroy();
        void setSliceSize(Time size);
        void gc();
        void printList(){
            // cout <<"current slice" << _curSlice->first << endl;
            for( auto it = _eventTree.begin(); it != _eventTree.end(); ++it)
                cout << it->first << endl;
        }
    private:
        //Singleton
        EventManager();
        Time _sliceSize;
        std::atomic<UINT64_T> _eventCnt;
        sl_map_gc<UINT64_T, shared_ptr<SliceEvents>> _eventTree;
        std::atomic<UINT64_T> _curSliceId;
        inline UINT64_T calcSlice(Time time)const;
    };

    inline int SliceEvents::insertEvent(const Event& event){
        NODE_ID node = event.first.getNodeId();
        auto nevents = make_shared<sl_map_gc<EventKey, shared_ptr<EventHandler>>>();
        _sliceEvs.insert(std::make_pair(node, nevents));
        auto itr = _sliceEvs.find(node);
        if(itr == _sliceEvs.end()){
            std::cout<<"有毛病"<<endl;
            return -1;
        }
        (itr->second)->insert(event);
        _eventCnt++;
        return 0;
    }
    inline UINT64_T EventManager::calcSlice(Time time)const
    {
        return time / _sliceSize;
    }
}


#endif