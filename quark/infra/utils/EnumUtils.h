#pragma once

#include <quark/quark.h>
#include <type_traits>

namespace quark {
class QKAPI EnumUtils {
public:
  template <typename E>
  static constexpr typename std::underlying_type<E>::type
  ToUnderlying(E e) noexcept;
};
} // namespace quark
