#ifndef _NSEVENT_H_
#define _NSEVENT_H_

#include <memory>
#include "Common.h"
#include <atomic>
#include "Time.h"
using std::shared_ptr;
using std::make_shared;
using std::pair;

namespace HSP_NS {
	
	class EventKey{
	public:
		EVENT_ID _eventId;
		NODE_ID _nodeId;
		Time _timestamp;
		EVENT_STATUS _status;
		String _desc; // 事件描述
		EventKey();
		EventKey(EVENT_ID event_id, NODE_ID node_id, Time timestamp, EVENT_STATUS status, const String &desc);
		EVENT_ID getEventId()const;
		NODE_ID getNodeId()const;
		Time getTimestamp()const;
		EVENT_STATUS getStatus()const;
		String getDescription()const;
		bool operator<(const EventKey& key2)const;
		bool operator>(const EventKey& key2)const;
		bool operator!=(const EventKey& key2)const;
	};

	class EventHandler {
	public:
		virtual void invoke()=0;
	};

 	using Event = pair<EventKey, shared_ptr<EventHandler>>;
	
	class EventMaker{
	public:
		static std::atomic<UINT64_T> NEXT_ID;
		/**
		* \copybrief MakeEvent(MEM,OBJ)
		* \tparam MEM \deduced The class method function signature(func).
		* \tparam OBJ \deduced The class type holding the method(object).
		* \tparam T1 \deduced Type of the argument to the underlying function.
		* \param [in] mem_ptr Class method member function pointer
		* \param [in] obj Class instance.
		* \param [in] a1 Argument value to be bound to the underlying function.
		* \returns The constructed EventImpl.
		*/ 
		template <typename MEM, typename OBJ> 
		static Event make_event(NODE_ID nodeId, Time timeToRun, const String& desc,
								MEM mem_ptr, OBJ obj);
		template <typename MEM, typename OBJ,
			      typename T1>
		static Event make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
								MEM mem_ptr, OBJ obj, T1 a1);
		template <typename MEM, typename OBJ,
				  typename T1, typename T2>
		static Event make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
								MEM mem_ptr, OBJ obj, T1 a1, T2 a2);				  
		template <typename MEM, typename OBJ,
				  typename T1, typename T2, typename T3>
		static Event make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
								MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3);
		template <typename MEM, typename OBJ,
				  typename T1, typename T2, typename T3, typename T4>
		static Event make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
								MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3, T4 a4);

		/**
		* \copybrief MakeEvent(void(*f)(void))
		* \tparam U1 \deduced Formal type of the argument to the function.
		* \tparam T1 \deduced Actual type of the argument to the function.
		* \param [in] f The function pointer.
		* \param [in] a1 Argument to be bound to the function.
		* \returns The constructed EventImpl.
		*/
		//Event make_event(void (*f)(void));
		//template <typename U1,
		//		  typename T1>
		//Event make_event(void (*f)(U1), T1 a1);
		//template <typename U1, typename U2,
		//	      typename T1, typename T2>
		//Event make_event(void (*f)(U1, U2), T1 a1, T2 a2);
		//template <typename U1, typename U2, typename U3,
		//		  typename T1, typename T2, typename T3>
		//Event make_event(void (*f)(U1, U2, U3), T1 a1, T2 a2, T3 a3);
	};

	template <typename MEM, typename OBJ>
	inline Event EventMaker::make_event(NODE_ID nodeId, Time timeToRun, const String& desc, MEM mem_ptr, OBJ obj){
		class EventMemberImpl0 : public EventHandler
		{
		public:
			EventMemberImpl0(OBJ obj, MEM function)
				: _obj(obj),
				_function(function)
				{}
			virtual ~EventMemberImpl0(){}
		private:
			virtual void invoke(void)
			{
				//(EventMemberImplObjTraits<OBJ>::GetReference(m_obj).*m_function)(m_a1, m_a2);
				((*_obj).*_function)();
			}
			OBJ _obj;
			MEM _function;
		};
		shared_ptr<EventHandler> evHandler = make_shared<EventMemberImpl0>(obj, mem_ptr);
		return std::make_pair(EventKey(NEXT_ID.fetch_add(1,std::memory_order_relaxed), nodeId, timeToRun, WAIT, desc), evHandler);
	}
	template <typename MEM, typename OBJ,
			  typename T1>
	inline Event EventMaker::make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
										MEM mem_ptr, OBJ obj, T1 a1){
		class EventMemberImpl1 : public EventHandler
		{
		public:
			EventMemberImpl1(OBJ obj, MEM function, T1 arg1)
				: _obj(obj),
				_function(function),
				_arg1(arg1)
				{}
			virtual ~EventMemberImpl1(){}
		private:
			virtual void invoke(void)
			{
				//(EventMemberImplObjTraits<OBJ>::GetReference(m_obj).*m_function)(m_a1, m_a2);
				((*_obj).*_function)(_arg1);
			}
			OBJ _obj;
			MEM _function;
			T1 _arg1;
		};
		shared_ptr<EventHandler> evHandler = make_shared<EventMemberImpl1>(obj, mem_ptr,a1);
		return std::make_pair(EventKey(NEXT_ID.fetch_add(1,std::memory_order_relaxed), nodeId, timeToRun, WAIT, desc), evHandler);
	}
	template <typename MEM, typename OBJ,
				typename T1,  typename T2>
	inline Event EventMaker::make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
										MEM mem_ptr, OBJ obj, T1 a1, T2 a2){
		class EventMemberImpl2 : public EventHandler
		{
		public:
			EventMemberImpl2(OBJ obj, MEM function, T1 arg1, T2 arg2)
				: _obj(obj),
				_function(function),
				_arg1(arg1),
				_arg2(arg2)
				{}
			virtual ~EventMemberImpl2(){}
		private:
			virtual void invoke(void)
			{
				//(EventMemberImplObjTraits<OBJ>::GetReference(m_obj).*m_function)(m_a1, m_a2);
				((*_obj).*_function)(_arg1, _arg2);
			}
			OBJ _obj;
			MEM _function;
			T1 _arg1;
			T2 _arg2;
		};
		shared_ptr<EventHandler> evHandler = make_shared<EventMemberImpl2>(obj, mem_ptr, a1, a2);
		return std::make_pair(EventKey(NEXT_ID.fetch_add(1,std::memory_order_relaxed), nodeId, timeToRun, WAIT, desc), evHandler);
	}

	template <typename MEM, typename OBJ,
			  typename T1,  typename T2, typename T3>
	inline Event EventMaker::make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
										MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3){
		class EventMemberImpl3 : public EventHandler
		{
		public:
			EventMemberImpl3(OBJ obj, MEM function, T1 arg1, T2 arg2, T3 arg3)
				: _obj(obj),
				_function(function),
				_arg1(arg1),
				_arg2(arg2),
				_arg3(arg3)
				{}
			virtual ~EventMemberImpl3(){}
		private:
			virtual void invoke(void)
			{
				//(EventMemberImplObjTraits<OBJ>::GetReference(m_obj).*m_function)(m_a1, m_a2);
				((*_obj).*_function)(_arg1, _arg2, _arg3);
			}
			OBJ _obj;
			MEM _function;
			T1 _arg1;
			T2 _arg2;
			T3 _arg3;
		};
		shared_ptr<EventHandler> evHandler = make_shared<EventMemberImpl3>(obj, mem_ptr,a1,a2,a3);
		return std::make_pair(EventKey(NEXT_ID.fetch_add(1,std::memory_order_relaxed), nodeId, timeToRun, WAIT, desc), evHandler);
	}

	template <typename MEM, typename OBJ,
			  typename T1,  typename T2, typename T3, typename T4>
	inline Event EventMaker::make_event(NODE_ID nodeId, Time timeToRun, const String& desc, 
										MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3, T4 a4){
		class EventMemberImpl4 : public EventHandler
		{
		public:
			EventMemberImpl4(OBJ obj, MEM function, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
				: _obj(obj),
				_function(function),
				_arg1(arg1),
				_arg2(arg2),
				_arg3(arg3),
				_arg4(arg4)
				{}
			virtual ~EventMemberImpl4(){}
		private:
			virtual void invoke(void)
			{
				//(EventMemberImplObjTraits<OBJ>::GetReference(m_obj).*m_function)(m_a1, m_a2);
				((*_obj).*_function)(_arg1, _arg2, _arg3);
			}
			OBJ _obj;
			MEM _function;
			T1 _arg1;
			T2 _arg2;
			T3 _arg3;
			T3 _arg4;
		};
		shared_ptr<EventHandler> evHandler = make_shared<EventMemberImpl4>(obj, mem_ptr, a1,a2,a3,a4);
		return std::make_pair(EventKey(NEXT_ID.fetch_add(1,std::memory_order_relaxed), nodeId, timeToRun, WAIT, desc), evHandler);
	}
	
}

#endif