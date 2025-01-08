#pragma once

#include <string>
#include "quark/build.h"

#ifdef __cplusplus

namespace quark
{
    class MTCXXAPI MTMime
    {
    public:
        static bool isImage(const std::string& path);
        static std::string getMimeType(const std::string& path);
    };
}

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
