#pragma once


#include <quark/quark.h>

#ifdef __cplusplus

extern "C" {
#endif

QKAPI void QKLogInfo(const char *message);

#ifdef __cplusplus
}

#include <string>

namespace quark {
    class QKAPI MTLogger {
    public:
        static MTLogger Standard;

        void LogInfo(const std::string &message);

        void LogInfo(std::initializer_list<std::string> messageList);

        void LogError(const std::string &message);

        void LogError(std::initializer_list<std::string> messageList);
    };

    QKAPI void MTLogInfo(const std::string &message);

    QKAPI void MTLogInfo(std::initializer_list<std::string> messageList);

    QKAPI void MTLogError(const std::string &message);

    QKAPI void MTLogError(std::initializer_list<std::string> messageList);
}


#endif
