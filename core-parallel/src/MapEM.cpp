#include "MapEM.h"
#include "Logger.h"
#include <iostream>
using namespace std;

namespace HSP_NS{

    
    // 要做到线程安全
    // 如果新插入一个node, 则需要使用全局锁(防止树的结构调整).
    // 如果node已经存在，使用局部锁.
    int SliceEvents::insertSafly(const Event& event){
        NODE_ID node = event.first.getNodeId();
        _glock.lock();
        if(_lLocks.find(node) == _lLocks.end())
        {
            shared_ptr<std::mutex> mutex_ = make_shared<std::mutex>();
            _lLocks.insert(std::make_pair(node, mutex_));
            auto nevents = make_shared<map<EventKey, shared_ptr<EventHandler>>>();
            _events.insert(std::make_pair(node, nevents));
        }
        _glock.unlock();
        _glock.lock_shared();
        _lLocks[node]->lock();
            _events[node]->insert(event);
            _totallEvent++;
        _lLocks[node]->unlock();
        _glock.unlock_shared();
        return 0;
    }


    EventManager::EventManager(){
        std::lock_guard<std::shared_mutex> lck (_glock);
        _eventCount = 0;
        _nodeNum = 0;
        _sliceSize = Time(NanoSecond, 3);
        _eventTree.insert(std::make_pair(0,make_shared<SliceEvents>(0)));
        _curSlice = _eventTree.begin();
    }
    EventManager& EventManager::getEventManager(){
        static EventManager singleton;
        return singleton;
    }

    int EventManager::insertEvent(const Event& event){
        Time time = event.first.getTimestamp();
        UINT64_T slice_id = calcSlice(time);
        _glock.lock();
        _eventCount += 1;
        if(_slices.find(slice_id) == _slices.end())
        {
            // WRITE_LOG(INFO, "Insert slice_id=%llu", slice_id);
            _slices.insert(slice_id);
            shared_ptr<SliceEvents> sevents = make_shared<SliceEvents>(slice_id);
            _eventTree.insert(std::make_pair(slice_id,sevents));    
        }
        _glock.unlock(); 
        _glock.lock_shared();
        _eventTree[slice_id]->insertSafly(event);
        _glock.unlock_shared();
        return 0;
    }

    UINT64_T EventManager::calcSlice(Time time)const{
        return time / _sliceSize;
    }

    void EventManager::destroy(){
        std::lock_guard<std::shared_mutex> lck (_glock);
        _eventTree.clear();
    }

    UINT64_T EventManager::getEventCount()const{
        std::shared_lock<std::shared_mutex> lck(_glock);
        return _eventCount;
    }

    int EventManager::peekNextSlice(shared_ptr<SliceEvents> &sliceEvents){
        _glock.lock_shared();
        _curSlice++;
        if(_curSlice == _eventTree.end())
            return -1;
        _glock.unlock_shared();
        sliceEvents = _curSlice->second;
        return 0;
    }

    void EventManager::setSliceSize(Time size){
        _sliceSize = size;
    }
    void EventManager::setNodeNum(UINT32_T num){
        _nodeNum = num;
    }

    void EventManager::gc(){
        std::lock_guard<std::shared_mutex> lck (_glock);
        _eventTree.erase(_eventTree.begin(), _curSlice);
    }
}