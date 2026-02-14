#include "hello.h"

namespace quark {

std::string hello(const std::string& name) {
    return std::string("Hello, ") + name + "!";
}

} // namespace quark