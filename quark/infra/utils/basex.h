#pragma once

#include <string>
#include <quark/quark.h>

namespace quark {
    QKAPI std::string decode64(const std::string &val);

    QKAPI std::string encode64(const std::string &val);
}
