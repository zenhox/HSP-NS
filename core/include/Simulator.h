#ifndef _NSSIMULATOR_H_
#define _NSSIMULATOR_H_

#include "Common.h"
#include "Time.h"
#include "EventManager.h"
#include "Event.h"
#include "Logger.h"


namespace HSP_NS {

	class Simulator {
	private:
		static Time _curTime;
		static EventManager& _eventManager ;
	public:
		static void run();
		static void destroy();
		static String getTimestamp(TIME_TYPE type);

		/**
		* desc: 事件的描述
		*/
		template <typename MEM, typename OBJ>
		static void schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj);
		template <typename MEM, typename OBJ, 
				  typename T1>
		static void schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj, T1 arg1);
		template <typename MEM, typename OBJ, 
				  typename T1, typename T2>
		static void schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj, T1 arg1, T2 arg2);
		template <typename MEM, typename OBJ, 
				  typename T1, typename T2, typename T3>
		static void schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj, T1 arg1, T2 arg2, T3 arg3);
		template <typename MEM, typename OBJ, 
				  typename T1, typename T2, typename T3, typename T4>
		static void schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj, T1 arg1, T2 arg2, T3 arg3, T4 arg4);
		// template <typename MEM, typename OBJ>
		// static void scheduleWithContext(Time delay, MEM mem_ptr, OBJ obj, NODE_ID node_id);
	};

	template <typename MEM, typename OBJ>
	inline void Simulator::schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj){
	    Event newEv =  EventMaker::make_event(nodeId, _curTime + delay, desc ,mem_ptr, obj);
	    _eventManager.insertEvent(newEv);
		WRITE_LOG(DEBUG, "[%ss] Insert event, node=%u, event_id=%llu, description: %s", 
			(newEv.first).getTimestamp().toString(Second).c_str(), 
			(newEv.first).getNodeId(),
			(newEv.first).getEventId(),
			(newEv.first).getDescription().c_str());
	}
	template <typename MEM, typename OBJ, 
				typename T1>
	inline void Simulator::schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj,
									T1 arg1)
	{
	    Event newEv =  EventMaker::make_event(nodeId, _curTime + delay, desc ,mem_ptr, obj, arg1);
	    _eventManager.insertEvent(newEv);
		WRITE_LOG(DEBUG, "[%ss] Insert event, node=%u, event_id=%llu, description: %s", 
			(newEv.first).getTimestamp().toString(Second).c_str(), 
			(newEv.first).getNodeId(),
			(newEv.first).getEventId(),
			(newEv.first).getDescription().c_str());
	}
	template <typename MEM, typename OBJ, 
			  typename T1, typename T2>
	inline void Simulator::schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj,
									T1 arg1, T2 arg2)
	{
	    Event newEv =  EventMaker::make_event(nodeId, _curTime + delay, desc ,mem_ptr, obj, arg1, arg2);
	    _eventManager.insertEvent(newEv);
		WRITE_LOG(DEBUG, "[%ss] Insert event, node=%u, event_id=%llu, description: %s", 
			(newEv.first).getTimestamp().toString(Second).c_str(), 
			(newEv.first).getNodeId(),
			(newEv.first).getEventId(),
			(newEv.first).getDescription().c_str());
	}
	template <typename MEM, typename OBJ, 
			  typename T1, typename T2, typename T3>
	inline void Simulator::schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj,
									T1 arg1, T2 arg2, T3 arg3)
	{
	    Event newEv =  EventMaker::make_event(nodeId, _curTime + delay, desc ,mem_ptr, obj, arg1, arg2, arg3);
	    _eventManager.insertEvent(newEv);
		WRITE_LOG(DEBUG, "[%ss] Insert event, node=%u, event_id=%llu, description: %s", 
			(newEv.first).getTimestamp().toString(Second).c_str(),  
			(newEv.first).getNodeId(),
			(newEv.first).getEventId(),
			(newEv.first).getDescription().c_str());
		return;
	}
	template <typename MEM, typename OBJ, 
			  typename T1, typename T2, typename T3, typename T4>
	inline void Simulator::schedule(NODE_ID nodeId, const Time &delay, const String& desc, MEM mem_ptr, OBJ obj,
									T1 arg1, T2 arg2, T3 arg3, T4 arg4)
	{
	    Event newEv =  EventMaker::make_event(nodeId, _curTime + delay, desc ,mem_ptr, obj, arg1, arg2, arg3, arg4);
	    _eventManager.insertEvent(newEv);
		WRITE_LOG(DEBUG, "[%ss] Insert event, node=%u, event_id=%llu, description: %s", 
			(newEv.first).getTimestamp().toString(Second).c_str(), 
			(newEv.first).getNodeId(),
			(newEv.first).getEventId(),
			(newEv.first).getDescription().c_str());
	}
}
#endif