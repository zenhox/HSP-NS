#ifndef _NSSIMULATOR_H_
#define _NSSIMULATOR_H_

#include "NSCommon.h"
#include "NSTime.h"
#include "NS3EventManager.h"
#include "NSEvent.h"

namespace HSP_NS {
	class Simulator {
	private:
		static Time _curTime;
		static EventManager& _eventManager ;
	public:
		static void run();
		static void destroy();

		/**
		* desc: 事件的描述
		*/
		template <typename MEM, typename OBJ>
		static void schedule(const Time &delay, MEM mem_ptr, OBJ obj, const std::string& desc);
		// template <typename MEM, typename OBJ>
		// static void scheduleWithContext(Time delay, MEM mem_ptr, OBJ obj, NODE_ID node_id);
	};

	template <typename MEM, typename OBJ>
	inline void Simulator::schedule(const Time & delay, MEM mem_ptr, OBJ obj, const std::string& desc){
	    Event newEv =  EventMaker::make_event(_curTime + delay, mem_ptr, obj, desc);
	    _eventManager.insertEvent(newEv);
	}
}
#endif