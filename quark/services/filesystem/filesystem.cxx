module;

#include "quark/quark.h"
#include "filesystem.h"

export module logger.filesystem;

export bool QKAPI IsFileExist(const std::string &filePath) {
    return quark::IsFileExist(filePath);
}