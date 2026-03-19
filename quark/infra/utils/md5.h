#pragma once

#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <string>

#include "quark/quark.h"

using boost::uuids::detail::md5;

namespace quark {
QKAPI std::string toString(const md5::digest_type &digest);

QKAPI std::string calcMd5(const std::string &content, bool formatUuid = false);
} // namespace quark
