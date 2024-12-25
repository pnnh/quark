#pragma once

#include <regex>
#include <string>
#include "quark/build.h"

#ifdef __cplusplus

namespace quark
{
    class MTAPI MTUUID
    {
    public:
        static bool isUUID(const std::string& uuid_string);
        static std::string generateUUID();
        static std::string generateShortUUID();
        static std::string generateUUIDWithoutHyphen();

    private:
        static std::regex uuid_regex;
    };
}

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
