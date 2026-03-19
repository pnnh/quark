#pragma once

#include "quark/quark.h"

#ifdef __cplusplus

#include <string>

namespace quark {
QKAPI std::string mime_type(const std::string &path);

class QKAPI MTMime {
public:
  static bool isImage(const std::string &path);

  static std::string getMimeType(const std::string &path);
};
} // namespace quark

extern "C" {
#endif

#ifdef __cplusplus
}
#endif