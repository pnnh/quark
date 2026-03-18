#pragma once

#include <string>

#include <quark/quark.h>


#ifdef __cplusplus

namespace quark
{
    class QKAPI MTUrl
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
