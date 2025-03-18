#include "regex.h"

#include <regex>

namespace quark
{
    bool MTRegex::isMatch(const std::string& str, const std::string& pattern)
    {
        std::regex re(pattern);
        return std::regex_match(str, re);
    }
}
