#pragma once

#include <string>

#ifdef __cplusplus

#include <quark/quark.h>

namespace quark {
// 校验是否合法的Email地址
QKAPI bool validateEmail(const std::string &email);

class QKAPI MTEMail {};
} // namespace quark

extern "C" {
#endif

#ifdef __cplusplus
}
#endif
