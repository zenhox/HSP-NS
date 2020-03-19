#include "NSEvent.h"

namespace HSP_NS {

	EventKey::EventKey(EVENT_ID event_id, NODE_ID node_id, Time timestamp, EVENT_STATUS status, const std::string& desc)
		: _eventId(event_id),
		_nodeId(node_id), 
		_timestamp(timestamp), 
		_status(status),
		_desc(desc)
	{}

	EventKey::EventKey()
		: _eventId(0),
		_nodeId(0), 
		_timestamp(), 
		_status(WAIT),
		_desc("empty")
	{}

	EVENT_ID EventKey::getEventId() const
	{
		return _eventId;
	}

	NODE_ID EventKey::getNodeId() const
	{
		return _nodeId;
	}

	Time EventKey::getTimestamp() const
	{
		return _timestamp;
	}

	EVENT_STATUS EventKey::getStatus() const
	{
		return _status;
	}

	std::string EventKey::getDescription()const{
		return _desc;
	}

	bool EventKey::operator<(const EventKey& key2)const{
		if(_timestamp != key2._timestamp)
			return _timestamp < key2._timestamp;
		else if(_eventId != key2._eventId)
			return _eventId < key2._eventId;
		return false;
	}
	
	UINT64_T EventMaker::NEXT_ID = 0;
}

