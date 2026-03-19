#pragma once

#include <quark/quark.h>

#ifdef __cplusplus

#include <string>

namespace quark {
class QKAPI PSRandom {
public:
  static int randomInt(int min, int max);

  static double randomDouble(double min, double max);

  static std::string randomString(int length);
};
} // namespace quark

extern "C" {
#endif

QKAPI int MTRandomInt(int min, int max);

#ifdef __cplusplus
}
#endif