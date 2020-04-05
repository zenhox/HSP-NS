#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include "Common.h"
using namespace g3;

#ifndef  _NO_LOG_
#define WRITE_LOG(level, printf_like_message, ...)                 \
if (!g3::logLevel(level)) {} else INTERNAL_LOG_MESSAGE(level).capturef(printf_like_message, ##__VA_ARGS__)
#else
    #define WRITE_LOG(level, printf_like_message, ...)    \
    while(0);
#endif

class Logger{
public:
    static String formatLog(const LogMessage& msg){
    // 精简化一下
        String out;
        out.append(msg.timestamp() + "\t"
                    + msg.level() + "\t("
                    + msg.threadID() + ")\t");
                    // + ":" + msg.line() + "]\t");
        return out;
    }

    static void initLogger(const String& logfile, const String& logpath){
        #ifndef _NO_LOG_
        static auto worker = g3::LogWorker::createLogWorker();
        static auto handle= worker->addDefaultLogger(logfile, logpath);
        g3::initializeLogging(worker.get());

        // change formater
        static auto changeFormatting = handle->call(&g3::FileSink::overrideLogDetails, formatLog);
        // static const String newHeader = "\t\tLOG format: [YYYY/MM/DD hh:mm:ss uuu* LEVEL THREAD_ID FILE->FUNCTION:LINE] message\n\t\t(uuu*: microseconds fractions of the seconds value)\n\n";
        static const String newHeader = "";
        // example of ovrriding the default formatting of header
        static auto changeHeader = handle->call(&g3::FileSink::overrideLogHeader, newHeader);

        changeFormatting.wait();
        changeHeader.wait();
        #endif  
    }
};

#endif