#pragma once

#include <expected>

#include "quark/build.h"
#include "quark/infra/result/result.h"


#ifdef __cplusplus

extern "C" {
#endif

CXAPI bool IsFileExist(const char *filePath);

#ifdef __cplusplus
}

#include <filesystem>
#include <string>

#include "quark/core/types/datetime.h"

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

        class CXAPI MTFileModel {
        public:
            explicit MTFileModel(std::string title);

            std::string URN;
            std::string Title;
            std::string Name;
            std::string Path;
            std::string Keywords;
            std::string Description;
            bool IsDir{};
            bool IsHidden{};
            bool IsIgnore{};
            quark::PSDatetime CreateTime;
            quark::PSDatetime UpdateTime;
        };

        class CXAPI MTFileServerBusiness {
        public:
            struct SelectFilesOptions {
                SelectFilesOptions();

                bool directories;
                bool files;
                bool hidden;
                bool ignore;
            };

            [[nodiscard]] static std::expected<std::vector<MTFileModel>,
                quark::MTCode>
            selectFilesVector(std::string parentPath,
                              SelectFilesOptions options = SelectFilesOptions());
        };
    }
}

#endif
