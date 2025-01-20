#pragma once

#include "quark/build.h"
#include <boost/beast/http.hpp>

namespace quark
{
    boost::beast::string_view mime_type(boost::beast::string_view path);
    class MTCXXAPI MTMime
    {
    public:
        static bool isImage(const std::string& path);
        static std::string getMimeType(const std::string& path);
    };
}
