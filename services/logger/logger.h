#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI void MTLogInfo(const char *message);

#ifdef __cplusplus
}

#include <string>

namespace quark {
    class CXAPI Logger {
    public:
        static void LogInfo(const std::string &message);

        static void LogInfo(std::initializer_list<std::string> messageList);
    };
}


#endif
