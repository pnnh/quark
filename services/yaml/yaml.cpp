#include "yaml.h"

#include "quark/types/string.hpp"
#include <regex>
#include <yaml-cpp/yaml.h>

std::string quark::YamlHandler::getString(const std::string &keyName) {
  // 多级key
  if (keyName.rfind('.', 0) > 0 &&
      std::regex_match(keyName, std::regex(R"(^(\w+\.)+\w+$)"))) {
    auto nameList = PSString::SplitChar(keyName, '.');
    YAML::Node node = _yamlConfig;
    for (const auto &name : nameList) {
      if (node[name]) {
        node = node[name];
      } else {
        return "";
      }
    }
    return std::string(node.as<std::string>());
  }
  // 一级key
  if (_yamlConfig[keyName]) {
    return std::string(_yamlConfig[keyName].as<std::string>());
  }

  return "";
}

quark::YamlHandler::YamlHandler(const std::string &filePath) {
  this->_yamlConfig = YAML::LoadFile(filePath);
}
