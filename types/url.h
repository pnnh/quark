#pragma once

#include <string>

#include "quark/build.h"

#ifdef __cplusplus

namespace quark
{
    class MTAPI MTUrl
    {
    public:
        static std::string encode(const std::string& url);
        static std::string decode(const std::string& url);
    };
}

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
