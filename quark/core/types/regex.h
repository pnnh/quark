#pragma once

#include <string>


#include <quark/quark.h>

#ifdef __cplusplus


namespace quark
{
    class QKAPI MTRegex
    {
    public:
        static bool isMatch(const std::string& str, const std::string& pattern);
    };
}

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
