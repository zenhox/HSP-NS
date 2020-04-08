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
    pool.enqueue(gc);

    shared_ptr<SliceEvents> sliceEvents; 
    std::vector< std::future<int> > results;
    results.reserve(100);

    // _eventManager.printList();
    
    while(!_eventManager.peekNextSlice(sliceEvents)){
        auto& events = sliceEvents->_sliceEvs;
        // cout << sliceEvents->getEventCount()<<endl;
        results.clear();
        for(auto it = events.begin(); it != events.end(); ++it){
            results.push_back(pool.enqueue(runOneNode,it->second));
        }
        for(size_t i=0; i<results.size(); ++i){
            results[i].wait(); 
        }
    }
}

void Simulator::setSliceSize(Time size){
    _eventManager.setSliceSize(size);
}

void Simulator::destroy(){
    WRITE_LOG(DEBUG, "Destroy the simulator");
    _eventManager.destroy();
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

int Simulator::runOneNode(shared_ptr<sl_map_gc<EventKey, shared_ptr<EventHandler>>> evList){
    int count = 0;
    for(auto it = evList->begin(); it != evList->end(); ++it){
        _curTimes[(it->first).getNodeId()] = (it->first).getTimestamp();
        (it->second)->invoke();
        count += 1;
    }
    return count;
}

int Simulator::gc(){
    _eventManager.gc();
    return 0;
}

}