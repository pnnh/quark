#pragma once

#include "quark/build.h"
#include <boost/url.hpp>
#include <optional>
#include <string>

namespace quark {
class CXAPI MTQueryString {
public:
  explicit MTQueryString(const std::string &url_string);

  [[nodiscard]] std::string getPath();
  [[nodiscard]] std::optional<std::string> getString(const std::string &key);
  std::optional<long> getLong(const std::string &key);

private:
  boost::urls::url_view parseUrl(const std::string &fullUrl);

  std::string _fullUrl;
  std::unique_ptr<boost::urls::url_view> _parsedUrl;
};
} // namespace quark
