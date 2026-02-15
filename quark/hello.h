#ifndef QUARK_HELLO_H
#define QUARK_HELLO_H

#include <string>
#include "build.h"

namespace quark {

CXAPI std::string hello(const std::string& name);

} // namespace quark

#endif //QUARK_HELLO_H