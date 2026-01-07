#include "filesystem.h"

#include <filesystem>
#include <fstream>
#include <quark/core/string/string.h>

#include "quark/infra/utils/md5.h"

bool quark::IsFileExist(const std::string &filePath) {
  std::ifstream inFile(filePath);
  return inFile.good();
}

std::string quark::JoinFilePath(std::initializer_list<std::string> pathList) {
  std::string temp;
  std::filesystem::path fullPath;
  for (const std::string &item: pathList) {
    std::filesystem::path itemPath(item);
    fullPath = fullPath / itemPath;
  }
  return fullPath.string();
}

std::string quark::PathFileName(const std::string &filePath) {
  std::filesystem::path itemPath(filePath);
  return itemPath.filename().string();
}

std::time_t
quark::convertFilesystemTime(const std::filesystem::file_time_type &fileTime) {
  auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
    fileTime - std::filesystem::file_time_type::clock::now() +
    std::chrono::system_clock::now());
  return std::chrono::system_clock::to_time_t(sctp);
}

quark::PSDatetime quark::fileLastModifyTime(const std::string &filePath) {
  std::filesystem::path itemPath(filePath);
  quark::PSDatetime lastTime{
    quark::convertFilesystemTime(last_write_time(itemPath))
  };
  return lastTime;
}

std::string quark::UserHomeDirectory() {
  if (char const *home = getenv("HOME");
    home or ((home = getenv("USERPROFILE")))) {
    return home;
  }
  char const *hdrive = getenv("HOMEDRIVE"), *hpath = getenv("HOMEPATH");
  return std::string(hdrive) + hpath;
}

std::string quark::ResolvePath(const std::string &path) {
  const std::string filePrefix = "file://";
  auto newPath = path;
  if (MTString::StartsWith(newPath, filePrefix)) {
    newPath = path.substr(filePrefix.length());
  }
  if (MTString::StartsWith(newPath, "~/")) {
    return UserHomeDirectory() + newPath.substr(1);
  } else if (MTString::StartsWith(newPath, "./")) {
    return std::filesystem::current_path().string() + newPath.substr(1);
  }
  return path;
}

std::string quark::filesystem::ReadAllText(const std::string &filePath) {
  std::ifstream inFile(filePath);
  std::string content((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());
  return content;
}

bool quark::isHidden(const std::string &path) {
  // todo: 处理在windows下面的隐藏文件类型
  if (path.rfind('.', 0) == 0) {
    return true;
  }
  return false;
}

// 一般不处理这些特殊的路径下面的文件
bool quark::isIgnore(const std::string &path) {
  // 隐藏文件和特殊目录
  if (isHidden(path) || path.find("node_modules") != std::string::npos ||
      path.find("build") != std::string::npos) {
    return true;
  }
  // 操作系统下面的特殊文件夹
  if (path.find("$RECYCLE.BIN") != std::string::npos ||
      path.find("System Volume Information") != std::string::npos) {
    return true;
  }

  return false;
}

bool IsFileExist(const char *filePath) {
  return quark::IsFileExist(filePath);
}

quark::filesystem::MTFileModel::MTFileModel(std::string title) {
  this->Title = title;
  this->CreateTime = std::chrono::system_clock::now();
  this->UpdateTime = std::chrono::system_clock::now();
}

quark::filesystem::MTFileServerBusiness::SelectFilesOptions::SelectFilesOptions() {
  directories = true; // 默认包含目录
  files = true; // 默认包含文件
  hidden = false; // 默认不包含隐藏文件
  ignore = false; // 默认不包含忽略文件
}

std::expected<std::vector<quark::filesystem::MTFileModel>, quark::MTCode>
quark::filesystem::MTFileServerBusiness::selectFilesVector(std::string parentPath,
                                                           SelectFilesOptions options) {
  const std::string fullPath = std::move(parentPath);
  if (!std::filesystem::exists(fullPath)) {
    return std::unexpected(quark::MTCode::IsNotDirectory);
  }
  if (!std::filesystem::is_directory(fullPath)) {
    return std::unexpected(quark::MTCode::IsNotDirectory);
  }
  auto files = std::vector<quark::filesystem::MTFileModel>();

  for (const auto &entry: std::filesystem::directory_iterator(fullPath)) {
    auto dirName = entry.path().filename();
    if (entry.path() == "." || entry.path() == "..") {
      continue;
    }
    if (!options.directories && entry.is_directory()) {
      continue;
    }
    if (!options.files && !entry.is_directory()) {
      continue;
    }
    if (!options.hidden && quark::isHidden(dirName.string())) {
      continue;
    }
    if (!options.ignore && quark::isIgnore(dirName.string())) {
      continue;
    }

    auto filePath = dirName.string();
    auto fileModel = quark::filesystem::MTFileModel(filePath);
    if (fileModel.URN.empty()) {
      fileModel.URN = quark::calcMd5(entry.path().string());
    }
    fileModel.IsDir = entry.is_directory();
    fileModel.IsHidden = quark::isHidden(filePath);
    fileModel.IsIgnore = quark::isIgnore(filePath);
    fileModel.Title = filePath;
    fileModel.Name = filePath;
    fileModel.Path = entry.path().string();

    fileModel.UpdateTime =
        quark::convertFilesystemTime(std::filesystem::last_write_time(entry));
    fileModel.CreateTime = fileModel.UpdateTime;
    files.emplace_back(fileModel);
  }

  return files;
}
