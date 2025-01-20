#pragma once

#include <boost/url.hpp>
#include <optional>
#include <string>
#include "quark/build.h"

namespace quark
{
  class MTCXXAPI MTQueryString
  {
  public:
    explicit MTQueryString(const std::string& url_string);

    [[nodiscard]] std::optional<std::string> getString(const std::string& key) const;
    std::optional<long> getLong(const std::string& key);

  private:
    std::string _fullUrl;
  };
}

