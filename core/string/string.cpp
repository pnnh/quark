#include "string.h"

#include <algorithm>
#include <sstream>
#include <utility>

#include "quark/infra/result/result.h"

template<typename... Args>
std::string quark::MTString::DynamicPrint(std::string_view rt_fmt_str,
                                          Args &&... args) {
  return std::vformat(rt_fmt_str, std::make_format_args(args...));
}

bool quark::MTString::IsBlank(const std::string &str) {
  return str.empty() ||
         std::all_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::isspace(c); });
}

bool quark::MTString::StartsWith(const std::string &str,
                                 const std::string &prefix) {
  return str.size() >= prefix.size() &&
         str.compare(0, prefix.size(), prefix) == 0;
}

std::string quark::MTString::LeftReplace(const std::string &str,
                                         const std::string &prefix,
                                         const std::string &newPrefix) {
  if (StartsWith(str, prefix)) {
    return newPrefix + str.substr(prefix.size());
  }
  return str;
}

bool quark::MTString::EndsWith(const std::string &str,
                               const std::string &suffix) {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::vector<std::string> quark::MTString::SplitChar(const std::string &str,
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
quark::MTString::SplitString(const std::string &str,
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

std::string quark::MTString::toLower(const std::string &str) {
  auto newStr = std::string(str);
  std::ranges::transform(newStr, newStr.begin(), ::tolower);
  return newStr;
}

std::string quark::MTString::toUpper(const std::string &str) {
  auto newStr = std::string(str);
  std::ranges::transform(newStr, newStr.begin(), ::toupper);
  return newStr;
}

std::string quark::MTString::trimAll(const std::string &orgStr,
                                     const std::string &str) {
  const std::string &newStr = orgStr;
  const std::string &newStr2 = trimLeft(newStr, str);
  return trimRight(newStr2, str);
}

std::string quark::MTString::trimLeft(const std::string &orgStr,
                                      const std::string &str) {
  auto newStr = std::string(orgStr);
  newStr.erase(0, newStr.find_first_not_of(str));
  return newStr;
}

std::string quark::MTString::trimRight(const std::string &orgStr,
                                       const std::string &str) {
  auto newStr = orgStr;
  newStr.erase(newStr.find_last_not_of(str) + 1);
  return newStr;
}

std::string quark::MTString::toStdString() const {
  return stringValue;
}

char *quark::MTString::getCString() const {
  return const_cast<char *>(stringValue.c_str());
}

quark::MTString::MTString() = default;

quark::MTString::MTString(std::string stdString)
  : stringValue(std::move(stdString)) {
}

quark::MTString &quark::MTString::operator=(const MTString &other) = default;

std::string quark::strToLower(const std::string &str) {
  return MTString::toLower(str);
}

auto QKStringToMTString(QKString *qkStr) -> quark::MTString {
  auto mtStr = static_cast<quark::MTString *>(qkStr->mtStr);
  return quark::MTString(mtStr->toStdString());
}

std::string QKStringToStdString(QKString *qkStr) {
  auto mtStr = static_cast<quark::MTString *>(qkStr->mtStr);
  return mtStr->toStdString();
}

QKString *StdStringToQKStringPtr(const std::string &stdString) {
  auto qkStr = new QKString();
  qkStr->mtStr = new quark::MTString(stdString);
  return qkStr;
}

QKString *QKStringCreate(char *data) {
  auto qkStr = new QKString();
  auto mtStr = new quark::MTString(data);
  qkStr->mtStr = mtStr;
  return qkStr;
}

int QKStringDelete(QKString * qkStr) {
  auto mtStr = static_cast<quark::MTString *>(qkStr->mtStr);
  if (mtStr) {
    delete mtStr;
    qkStr->mtStr = nullptr;
  }
  delete qkStr;
  return QKResultOk;
}

char *QKStringGetData(QKString *qkStr) {
  auto mtStr = static_cast<quark::MTString *>(qkStr->mtStr);

  return mtStr->getCString();
}
