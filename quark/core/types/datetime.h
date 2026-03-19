#pragma once

#include <chrono>
#include <ctime>
#include <string>

#include "quark/quark.h"

namespace quark {
QKAPI std::chrono::system_clock::time_point makeTimePoint(const std::string &s);

QKAPI std::string
formatTime(const std::chrono::system_clock::time_point &time_point);

class QKAPI PSDatetime {
public:
  explicit PSDatetime();
  explicit PSDatetime(const std::string &datetime);
  explicit PSDatetime(const std::chrono::system_clock::time_point &datetime);
  explicit PSDatetime(const std::time_t &datetime);

  PSDatetime &operator=(const PSDatetime &other);
  PSDatetime &operator=(const std::chrono::system_clock::time_point &x);
  PSDatetime &operator=(const std::time_t &datetime);

  [[nodiscard]]
  std::string toString() const;
  [[nodiscard]] std::chrono::system_clock::time_point toTimePoint() const;

  static PSDatetime now();

private:
  std::chrono::system_clock::time_point timeValue;
};
} // namespace quark
