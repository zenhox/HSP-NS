#include "MapEM.h"
#include "Logger.h"
#include <iostream>
#include <ctime>
using namespace std;

namespace HSP_NS{

    SliceEvents::SliceEvents(UINT64_T id){
        _sliceId = 0;
        _eventCnt.store(0);
    }

    SliceEvents::~SliceEvents(){}

    UINT64_T SliceEvents::getEventCount()const{
        return _eventCnt.load();
    }

    UINT64_T SliceEvents::getSliceId()const{
        return _sliceId;
    }

    EventManager::EventManager(){
        _eventCnt.store(0);
        _sliceSize = Time(NanoSecond, 3);
        _eventTree.insert(std::make_pair(0,make_shared<SliceEvents>(0)));
        _curSliceId = 0;
    }
    EventManager& EventManager::getEventManager(){
        static EventManager singleton;
        return singleton;
    }

    int EventManager::insertEvent(const Event& event){
        UINT64_T slice_id = calcSlice(event.first.getTimestamp());
        if(slice_id != 0 && slice_id <= _curSliceId)
        {
            cout<<"发现了片内插入"<<_curSliceId<<endl;
        }
        shared_ptr<SliceEvents> sevents = make_shared<SliceEvents>(slice_id);
        auto re = _eventTree.insert(std::make_pair(slice_id,sevents));   
        // if(re.second == false)
	    // {
        //     auto itr = _eventTree.find(slice_id);
	    //     if((itr->second)->getEventCount() == 0)
		//     cout << "insert 有问题"<<endl;
	    // }
        // else
        //     cout << "插入OK" << endl;
        auto itr = _eventTree.find(slice_id);
        (itr->second)->insertEvent(event);
        _eventCnt++;
        return 0;
    }


    void EventManager::destroy(){}

    UINT64_T EventManager::getEventCount()const{
        return _eventCnt.load();
    }

    int EventManager::peekNextSlice(shared_ptr<SliceEvents> &sliceEvents){
        static bool isBegin = true;

        auto itr = _eventTree.find(_curSliceId.load());
        if(_curSliceId.load() == 0)
        {      
            if( isBegin && (itr->second)->getEventCount() != 0)
            {
                sliceEvents = itr->second;
                isBegin = false;
                return 0;
            }
        }
        itr++;
        if(itr.isNull())
        {
            // cout << itr->first << endl;
            // printList();
            _curSliceId.store(0);
            return -1;
        }   
        _curSliceId.store(itr->first);     
        sliceEvents = itr->second;
        return 0;
    }

    void EventManager::setSliceSize(Time size){
        _sliceSize = size;
    }

    void EventManager::gc(){
        cout << "执行一次gc, 执行前size=" << _eventTree.size()<<endl;
        clock_t bg = clock();
        int count = 9988;
        auto itr = _eventTree.begin();
        while(count--)
            itr = _eventTree.erase(itr);
        clock_t ed = clock();
        cout << "耗费时间" << (double)(ed-bg)/CLOCKS_PER_SEC <<", 执行后size=" << _eventTree.size()<<endl;
    }
}
