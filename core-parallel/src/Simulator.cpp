#include "Simulator.h"
#include <vector>
#include <future>
#if defined THREAD_POOL_A
#include "ThreadPool.h"
#endif
#if defined THREAD_POOL_B
#include "threadpool11/threadpool11.hpp"
#endif
namespace HSP_NS{

map<NODE_ID, Time> Simulator::_curTimes;

EventManager& Simulator::_eventManager = EventManager::getEventManager();

size_t getIndexND(size_t nd){
    if(nd > 10)
        return 3;
    else if(nd > 6)
        return 2;
    else if(nd > 1)
        return 1;
    else 
        return 0;
}
size_t getIndexEV(UINT64_T ev){
    if(ev > 100)
        return 3;
    else if(ev > 50)
        return 2;
    else if(ev > 10)
        return 1;
    else 
        return 0;  
}

void Simulator::run(UINT32_T threadNum){
    if(threadNum <= 0)
    {   
        WRITE_LOG(FATAL, "Thread num cannot lower than zero.");
        exit(-1);
    }

    shared_ptr<SliceEvents> sliceEvents; 
    std::vector< std::future<void> > results;
    results.reserve(100);
    int nodeStatis[4]=  {0};    //1, 2~6, 7~10, 11~, 
    int evetStatis[4] = {0};    //0~10, 11 ~ 50, 51 ~ 100, 100~
    int count = 0;

    #if defined THREAD_POOL_A
    ThreadPool pool(threadNum);
    while(!_eventManager.peekNextSlice(sliceEvents)){
        count ++ ;
        auto& events = sliceEvents->_sliceEvs;
        // cout << sliceEvents->getEventCount()<<endl;
        UINT64_T evCnt = sliceEvents->getEventCount();
        size_t ndCnt = events.size();
        nodeStatis[getIndexND(ndCnt)]++;
        evetStatis[getIndexEV(evCnt)]++;
        results.clear();
        for(auto it = events.begin(); it != events.end(); ++it){
            results.emplace_back(pool.enqueue(runOneNode,it->second));
        }
        for(size_t i=0; i<results.size(); ++i){
            results[i].wait(); 
        }
        if(count % 100000 == 0){
            pool.enqueue(gc);
        }
    }
    #endif
    #if defined THREAD_POOL_B
    threadpool11::pool pool;
    pool.set_worker_count(threadNum);
    while(!_eventManager.peekNextSlice(sliceEvents)){
        count ++ ;
        auto& events = sliceEvents->_sliceEvs;
        // cout << sliceEvents->getEventCount()<<endl;
        UINT64_T evCnt = sliceEvents->getEventCount();
        size_t ndCnt = events.size();
        nodeStatis[getIndexND(ndCnt)]++;
        evetStatis[getIndexEV(evCnt)]++;
        results.clear();
        for(auto it = events.begin(); it != events.end(); ++it){
            auto& evList = it->second;
            results.emplace_back(pool.post_work<void>([evList]() { return runOneNode(evList); }));
        }
        for(size_t i=0; i<results.size(); ++i){
            results[i].wait(); 
        }
        if(count % 100000 == 0){
            pool.post_work<void>(gc);
        }
    }
    #endif

    //输出统计结果
    for(auto i=0; i<4; ++i){
        cout << nodeStatis[i] << "    ";
    }
    cout << endl;
    for(auto i=0; i<4; ++i){
        cout << evetStatis[i] << "    ";
    }
    cout << endl;
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

void Simulator::runOneNode(shared_ptr<sl_map_gc<EventKey, shared_ptr<EventHandler>>> evList){
    for(auto it = evList->begin(); it != evList->end(); ++it){
        _curTimes[(it->first).getNodeId()] = (it->first).getTimestamp();
        (it->second)->invoke();
    }
}

int Simulator::gc(){
    _eventManager.gc();
    return 0;
}

}