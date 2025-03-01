
#include "channel.h"
#include <filesystem>
#include <string>

#include "quark/services/filesystem/filesystem.hpp"
#include "quark/services/yaml/yaml.h"
#include "quark/types/string.hpp"
#include "quark/utils/md5.h"

quark::ChannelServerBusiness::ChannelServerBusiness(
    const std::string &baseUrl) {
  this->baseUrl = baseUrl;
}

std::shared_ptr<std::vector<quark::PSChannelModel>>
quark::ChannelServerBusiness::selectChannels() const {
  auto channels = std::make_shared<std::vector<PSChannelModel>>();

  for (const auto &entry : std::filesystem::directory_iterator(this->baseUrl)) {
    auto dirName = entry.path().filename();
    if (entry.path() == "." || entry.path() == ".." || !entry.is_directory()) {
      continue;
    }

    auto filePath = dirName.string();
    if (!isChannelDirectory(filePath)) {
      continue;
    }
    auto channelModel = quark::PSChannelModel(filePath);
    auto metadataFilePath =
        quark::JoinFilePath({this->baseUrl, filePath, "metadata.yaml"});
    if (quark::IsFileExist(metadataFilePath)) {
      auto yamlHandler = quark::YamlHandler(metadataFilePath);
      channelModel.URN =
          quark::MTString::toLower(yamlHandler.getString("metadata.urn"));
      channelModel.Title = yamlHandler.getString("metadata.title");
      channelModel.Description = yamlHandler.getString("metadata.description");
      channelModel.Image = yamlHandler.getString("metadata.image");
    }
    channelModel.Path = entry.path().string();
    if (channelModel.URN.empty()) {
      channelModel.URN =
          quark::MTString::toLower(quark::calcMd5(entry.path().string()));
    }
    channels->emplace_back(channelModel);
  }

  return channels;
}

bool quark::isChannelDirectory(const std::string &directoryName) {
  return quark::MTString::EndsWith(directoryName, ".chan") ||
         quark::MTString::EndsWith(directoryName, ".channel") ||
         quark::MTString::EndsWith(directoryName, ".notechannel");
}
