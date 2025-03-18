#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI void QKLogInfo(const char* message);

#ifdef __cplusplus
}

#include <string>

namespace quark
{
    class CXAPI MTLogger
    {
    public:
        static MTLogger Standard;
        void LogInfo(const std::string& message);
        void LogInfo(std::initializer_list<std::string> messageList);

        void MTLogError(const std::string& message);
        void MTLogError(std::initializer_list<std::string> messageList);
    };

    void MTLogInfo(const std::string& message);
    void MTLogInfo(std::initializer_list<std::string> messageList);

    void MTLogError(const std::string& message);
    void MTLogError(std::initializer_list<std::string> messageList);
}


#endif
