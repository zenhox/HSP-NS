#ifndef _NSCOMMON_H_
#define _NSCOMMON_H_
#include <string>
#include <memory>
using std::shared_ptr;
using std::make_shared;

// Data Type
using INT32_T = int;
using INT64_T = long;
using UINT32_T = unsigned int;
using UINT64_T = unsigned long long;

using NODE_ID = unsigned int;
using EVENT_ID = unsigned long long;

using String=std::string;

// Event Status
enum EVENT_STATUS {WAIT, RUNNING, DONE};

// Time
enum TIME_TYPE {Second, MilliSecond, MicroSecond, NanoSecond, BaseTime};
#define SLICES_PER_SECOND 1000000000000
#define SLICES_PER_MILLIS 1000000000
#define SLICES_PER_MICROS 1000000
#define SLICES_PER_NANOSE 1000


#endif