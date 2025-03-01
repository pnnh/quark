#pragma once
#include "quark/build.h"
#include <string>

namespace quark
{
    CXAPI std::string decode64(const std::string& val);
    CXAPI std::string encode64(const std::string& val);
}
