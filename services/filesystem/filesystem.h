#pragma once

#include "quark/build.h"


#ifdef __cplusplus

extern "C" {
#endif

CXAPI bool IsFileExist(const char *filePath);

#ifdef __cplusplus
}

#include <filesystem>
#include <string>

#include "quark/types/datetime.hpp"

namespace quark {
    bool CXAPI IsFileExist(const std::string &filePath);

    std::string JoinFilePath(std::initializer_list<std::string> pathList);

    std::string PathFileName(const std::string &filePath);

    std::time_t
    convertFilesystemTime(const std::filesystem::file_time_type &fileTime);

    PSDatetime fileLastModifyTime(const std::string &filePath);

    bool isHidden(const std::string &path);

    bool isIgnore(const std::string &path);

    // 返回不同平台下的用户主目录
    std::string UserHomeDirectory();

    // 解析路径，将一些占位符替换为特殊目录
    std::string ResolvePath(const std::string &path);

    namespace filesystem {
        std::string ReadAllText(const std::string &filePath);
    }
}

#endif
