#pragma once
#include "quark/build.h"
#include <string>

namespace quark
{
    MTCXXAPI std::string decode64(const std::string& val);
    MTCXXAPI std::string encode64(const std::string& val);
}
