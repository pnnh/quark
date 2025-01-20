#include "file.hpp"
#include <string>
#include <filesystem>
#include "quark/services/filesystem/filesystem.hpp"
#include "quark/types/datetime.hpp"
#include "quark/utils/md5.h"
#include "quark/types//String.h"


quark::FileServerBusiness::SelectFilesOptions::SelectFilesOptions()
{
    directories = true; // 默认包含目录
    files = true;    // 默认包含文件
    hidden = false; // 默认不包含隐藏文件
    ignore = false; // 默认不包含忽略文件
}

std::vector<quark::PSFileModel> quark::FileServerBusiness::selectFilesVector(std::string parentPath,
            SelectFilesOptions options)
{
    auto files = std::vector<PSFileModel>();

    const std::string fullPath = std::move(parentPath);

    for (const auto& entry : std::filesystem::directory_iterator(fullPath))
    {
        auto dirName = entry.path().filename();
        if (entry.path() == "." || entry.path() == "..")
        {
            continue;
        }
        if (!options.directories && entry.is_directory())
        {
            continue;
        }
        if (!options.files && !entry.is_directory())
        {
            continue;
        }
        if (!options.hidden && isHidden(dirName.string()))
        {
            continue;
        }
        if (!options.ignore && isIgnore(dirName.string()))
        {
            continue;
        }

        auto filePath = dirName.string();
        auto fileModel = quark::PSFileModel(filePath);
        if (fileModel.URN.empty())
        {
            fileModel.URN = quark::calcMd5(entry.path().string());
        }
        fileModel.IsDir = entry.is_directory();
        fileModel.IsHidden = quark::isHidden(filePath);
        fileModel.IsIgnore = quark::isIgnore(filePath);
        fileModel.Title = filePath;
        fileModel.Name = filePath;
        fileModel.Path = entry.path().string();

        fileModel.UpdateTime = quark::convertFilesystemTime(std::filesystem::last_write_time(entry));
        fileModel.CreateTime = fileModel.UpdateTime;
        files.emplace_back(fileModel);
    }

    return files;
}
