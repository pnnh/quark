#include "query.h"

#include "Exception.h"
#include "string.hpp"

#include <boost/range/algorithm.hpp>
#include <regex>

quark::MTQueryString::MTQueryString(const std::string &url_string) {
  auto fullUrl = std::string(url_string);
  if (!quark::PSString::StartsWith(fullUrl, "http://") &&
      !quark::PSString::StartsWith(fullUrl, "https://")) {
    if (fullUrl.empty()) {
      throw quark::PSException(quark::QuantumEnum::ERROR,
                               "url_string is empty");
    }
    fullUrl = std::string("http://localhost") + fullUrl;
  }

  this->_fullUrl = fullUrl;
  this->_parsedUrl =
      std::make_unique<boost::urls::url_view>(parseUrl(this->_fullUrl));
}

std::string quark::MTQueryString::getPath() { return this->_parsedUrl->path(); }

boost::urls::url_view
quark::MTQueryString::parseUrl(const std::string &fullUrl) {
  auto parseResult = boost::urls::parse_uri(fullUrl);
  if (parseResult.has_error()) {
    throw quark::PSException(quark::QuantumEnum::ERROR,
                             std::string("url parse error") +
                                 parseResult.error().to_string());
  }
  return parseResult.value();
}

std::optional<std::string>
quark::MTQueryString::getString(const std::string &name) {
  const auto it = boost::range::find_if(
      this->_parsedUrl->params(),
      [name](const boost::urls::param &p) { return p.key == name; });

  if (it != this->_parsedUrl->params().end()) {
    return (*it).value;
  }
  return std::nullopt;
}

std::optional<long> quark::MTQueryString::getLong(const std::string &key) {
  auto it = boost::range::find_if(
      this->_parsedUrl->params(),
      [key](boost::urls::param p) { return p.key == key; });

  if (it != this->_parsedUrl->params().end()) {
    return std::stol((*it).value);
  }
  return std::nullopt;
}
