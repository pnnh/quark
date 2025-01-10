module;

#include "quark/build.h"
#include "filesystem.hpp"

export module logger.filesystem;

export bool MTCXXAPI IsFileExist(const std::string& filePath) {
    return quark::IsFileExist(filePath);
}
