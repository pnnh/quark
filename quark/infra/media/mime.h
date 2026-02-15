#pragma once


#include "quark/build.h"


#ifdef __cplusplus

#include <string>


namespace quark {
    std::string mime_type(const std::string &path);

    class CXAPI MTMime {
    public:
        static bool isImage(const std::string &path);

        static std::string getMimeType(const std::string &path);
    };
}


extern "C" {
#endif


#ifdef __cplusplus
}
#endif