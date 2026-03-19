#pragma once

#include <quark/quark.h>
#include <string>
#include <yaml-cpp/node/node.h>

namespace quark {
class QKAPI YamlHandler {
public:
  explicit YamlHandler(const std::string &filePath);

  std::string getString(const std::string &keyName);

private:
  std::string _filePath;
  YAML::Node _yamlConfig;
};
} // namespace quark
