#pragma once

#include <string>
#include "quark/build.h"

namespace quark
{
    class MTCXXAPI Logger
    {
    public:
        static void LogInfo(const std::string& message);
        static void LogInfo(std::initializer_list<std::string> messageList);
    };
}
