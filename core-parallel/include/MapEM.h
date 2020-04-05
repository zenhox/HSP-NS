#ifndef _NSEVENTMANAGER_H_
#define _NSEVENTMANAGER_H_

#include "Common.h"
#include "Event.h"
#include <map>
#include <set>
#include <memory>
#include <mutex>  // 对于 std::unique_lock
#include <shared_mutex>
#include <thread>
using std::map;
using std::shared_ptr;
using std::pair;
using std::set;


namespace HSP_NS{
    
    struct SliceEvents{
        SliceEvents(UINT64_T id):_sliceId(id),_totallEvent(0)
        {
            
        }
        // 要做到线程安全
        // 如果新插入一个node, 则需要使用全局锁(防止树的结构调整).
        // 如果node已经存在，使用局部锁.
        int insertSafly(const Event& event);

        UINT64_T _sliceId;
        UINT64_T _totallEvent;
        mutable std::shared_mutex _glock;  // 需要使用 glock 才能访问的到
        map<NODE_ID, shared_ptr<map<EventKey, shared_ptr<EventHandler>>>> _events;
        map<NODE_ID, shared_ptr<std::mutex>> _lLocks;
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
        void setNodeNum(UINT32_T num);
        void gc();
    private:
        UINT64_T _eventCount;
        UINT32_T _nodeNum;
        Time _sliceSize;
        map<UINT64_T, shared_ptr<SliceEvents>> _eventTree;
        set<UINT64_T> _slices; //目前那些时间片有事件
        map<UINT64_T, shared_ptr<SliceEvents>>::iterator _curSlice;
        mutable std::shared_mutex _glock;
        //Singleton
        EventManager();
        UINT64_T calcSlice(Time time)const;
    };

}


#endif