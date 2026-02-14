#pragma once

#include "build.h"
#include <string>

namespace quark
{
     CXAPI std::string markdownToHtml(const std::string& markdownText);
}
