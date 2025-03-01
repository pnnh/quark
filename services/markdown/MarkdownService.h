#pragma once

#include "quark/build.h"
#include <string>

namespace quark
{
     CXAPI std::string markdownToHtml(const std::string& markdownText);
}
