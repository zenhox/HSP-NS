#ifndef _NSCOMMON_H_
#define _NSCOMMON_H_

namespace HSP_NS {
	// Data Type
	using INT32_T = int;
	using INT64_T = long;
	using UINT32_T = unsigned int;
	using UINT64_T = unsigned long long;

	using NODE_ID = unsigned int;
	using EVENT_ID = unsigned long long;

	// Event Status
	enum EVENT_STATUS {WAIT, RUNNING, DONE};
	enum TIME_TYPE {Second, MilliSecond, MicroSecond, NanoSecond, BaseTime};
};

#endif