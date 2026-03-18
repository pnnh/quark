#pragma once

#include "quark/quark.h"

#ifdef __cplusplus

extern "C" {
#endif

const int QKResultOk = 0;
const int QKResultError = 1;

QKAPI constexpr const char *QKResultCodeToString(int qkCode);
#ifdef __cplusplus
}

#include <iostream>
#include <optional>
#include <string>
#include <variant>

namespace quark {
  enum class QKAPI MTCode {
    Ok = 0,
    Error = 1,
    IsNotDirectory = 2,
    IsNotFile = 3,
    IsNotExist = 4,
    SqlSelectFailed = 5, // 数据库查询出错
  };

  std::ostream &operator<<(std::ostream &os, quark::MTCode color);

  std::string MTCodeToString(MTCode mtCode);

  class QKAPI MTException final : public std::exception {
  public:
    MTException();

    explicit MTException(const int &code);

    explicit MTException(const std::string &message);

    explicit MTException(const int &code, const std::string &message);

    ~MTException() override;

    int code();

    const std::string message();

    void appendMessage(const std::string &message);

    [[nodiscard]]
    const char *what() const noexcept override;

  private:
    int code_;
    std::string message_;
  };

  template<class T>
  class QKAPI MTResult {
  public:
    explicit MTResult(const T &rhs) : v_(rhs) {
    }

    explicit MTResult(const T &&rhs) : v_(std::move(rhs)) {
    }

    explicit MTResult(const MTException &rhs) : v_(rhs) {
    }

    explicit MTResult(const MTException &&rhs) : v_(std::move(rhs)) {
    }

    [[nodiscard]] bool has_error() const {
      return std::holds_alternative<MTException>(v_);
    }

    const T &value() const { return std::get<T>(v_); };

    [[nodiscard]] const MTException &error() const {
      return std::get<MTException>(v_);
    };

  private:
    MTResult() = default;

    T TakeValue() && { return std::get<T>(std::move(v_)); }

    std::variant<T, MTException> v_;
  };
} // namespace quark

#endif
