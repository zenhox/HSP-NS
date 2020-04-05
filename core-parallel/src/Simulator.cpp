#include "Simulator.h"
#include <vector>
#include <future>

namespace HSP_NS{

map<NODE_ID, Time> Simulator::_curTimes;

EventManager& Simulator::_eventManager = EventManager::getEventManager();
void Simulator::run(UINT32_T threadNum){
    if(threadNum <= 0)
    {   
        WRITE_LOG(FATAL, "Thread num cannot lower than zero.");
        exit(-1);
    }
    ThreadPool pool(threadNum);
    shared_ptr<SliceEvents> sliceEvents;  //map<NODE_ID, shread_ptr<map<EventKey, shared_ptr<EventHandler>>>>
    std::vector< std::future<int> > results;
    results.reserve(100);
    int count = 0;
    while(!_eventManager.peekNextSlice(sliceEvents)){
        count += 1;
        // WRITE_LOG(INFO, "Run slice_id=%llu", sliceEvents->_sliceId);
        auto& events = sliceEvents->_events;
        // 理论上来讲，当前时间片不会有其他插入了.
        results.clear();
        for(auto it = events.begin(); it != events.end(); ++it){
            // 将不同节点的任务分配给不同的线程
            // NODE_ID node = it->first;
            results.push_back(pool.enqueue(runOneNode,it->second));
        }
        if(count % 100 == 0){
            pool.enqueue(gc);
            WRITE_LOG(INFO, "GC run once.");
        }
        for(size_t i=0; i<results.size(); ++i){
            results[i].get();  // 等待所有线程都完成.
        }
        // 开启下一个时间片
    }
}

void Simulator::setSliceSize(Time size){
    _eventManager.setSliceSize(size);
}

void Simulator::destroy(){
    _eventManager.destroy();
    WRITE_LOG(DEBUG, "Destroy the simulator");
}


String Simulator::getTimestamp(NODE_ID node, TIME_TYPE type){
    if(_curTimes.find(node) == _curTimes.end())
        _curTimes.insert(std::make_pair(node, Time(Second,0)));
    return _curTimes[node].toString(type);
}

Time Simulator::getTimestamp(NODE_ID node, Time delay){
    if(_curTimes.find(node) == _curTimes.end())
        _curTimes.insert(std::make_pair(node, Time(Second,0)));
    return _curTimes[node] + delay;
}

UINT64_T Simulator::getEventCount(){
    return _eventManager.getEventCount();
}

int Simulator::runOneNode(shared_ptr<map<EventKey, shared_ptr<EventHandler>>> evList){
    int count = 0;
    for(auto it = evList->begin(); it != evList->end(); ++it){
        _curTimes[(it->first).getNodeId()] = (it->first).getTimestamp();
        (it->second)->invoke();
        count += 1;
    }
    return count;
}

void Simulator::gc(){
    _eventManager.gc();
}

}