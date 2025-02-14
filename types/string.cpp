#include "string.hpp"

#include <algorithm>
#include <sstream>
#include <utility>

template <typename... Args>
std::string quark::PSString::DynamicPrint(std::string_view rt_fmt_str,
                                          Args &&...args) {
  return std::vformat(rt_fmt_str, std::make_format_args(args...));
}

bool quark::PSString::IsBlank(const std::string &str) {
  return str.empty() ||
         std::all_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::isspace(c); });
}

bool quark::PSString::StartsWith(const std::string &str,
                                 const std::string &prefix) {
  return str.size() >= prefix.size() &&
         str.compare(0, prefix.size(), prefix) == 0;
}

std::string quark::PSString::LeftReplace(const std::string &str,
                                         const std::string &prefix,
                                         const std::string &newPrefix) {
  if (StartsWith(str, prefix)) {
    return newPrefix + str.substr(prefix.size());
  }
  return str;
}

bool quark::PSString::EndsWith(const std::string &str,
                               const std::string &suffix) {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::vector<std::string> quark::PSString::SplitChar(const std::string &str,
                                                    char delimiter) {
  std::vector<std::string> stringList;
  std::istringstream iss(str);
  std::string item;
  while (getline(iss, item, delimiter)) {
    stringList.push_back(item);
  }
  return stringList;
}
std::vector<std::string>
quark::PSString::SplitString(const std::string &str,
                             const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
    end = str.find(delimiter, start);
  }
  tokens.push_back(str.substr(start, end));

  return tokens;
}

std::string quark::PSString::toLower(const std::string &str) {
  auto newStr = std::string(str);
  std::ranges::transform(newStr, newStr.begin(), ::tolower);
  return newStr;
}

std::string quark::PSString::toUpper(const std::string &str) {
  auto newStr = std::string(str);
  std::ranges::transform(newStr, newStr.begin(), ::toupper);
  return newStr;
}

std::string quark::PSString::trimAll(const std::string &orgStr,
                                     const std::string &str) {
  const std::string &newStr = orgStr;
  const std::string &newStr2 = trimLeft(newStr, str);
  return trimRight(newStr2, str);
}

std::string quark::PSString::trimLeft(const std::string &orgStr,
                                      const std::string &str) {
  auto newStr = std::string(orgStr);
  newStr.erase(0, newStr.find_first_not_of(str));
  return newStr;
}

std::string quark::PSString::trimRight(const std::string &orgStr,
                                       const std::string &str) {
  auto newStr = orgStr;
  newStr.erase(newStr.find_last_not_of(str) + 1);
  return newStr;
}

quark::PSString::PSString() = default;

quark::PSString::PSString(std::string stdString)
    : stringValue(std::move(stdString)) {}

quark::PSString &quark::PSString::operator=(const PSString &other) = default;

std::string quark::strToLower(const std::string &str) {
  return PSString::toLower(str);
}