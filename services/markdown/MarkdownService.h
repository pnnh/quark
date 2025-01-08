#pragma once

#include "quark/build.h"
#include <string>

namespace quark
{
     MTCXXAPI std::string markdownToHtml(const std::string& markdownText);
}
