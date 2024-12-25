#pragma once

#include "quark/build.h"
#include <string>

namespace quark
{
     MTAPI std::string markdownToHtml(const std::string& markdownText);
}
