#pragma once

#include <quark/build.h>

#ifdef __cplusplus


extern "C" {
CXAPI constexpr int QKResultOk = 0;
CXAPI constexpr int QKResultError = 1;

CXAPI constexpr const char *QKResultCodeToString(int qkCode) {
  switch (qkCode) {
  case QKResultOk:
    return "OK";
  case QKResultError:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

#endif

#ifdef __cplusplus
}

#include <iostream>
#include <optional>
#include <string>
#include <variant>

namespace quark {
class CXAPI MTException final : public std::exception {
public:
  MTException();

  explicit MTException(const int &code);

  explicit MTException(const std::string &message);

  explicit MTException(const int &code, const std::string &message);

  int code();
  const std::string message();

  void appendMessage(const std::string &message);

  [[nodiscard]]
  const char *what() const noexcept override {
    return QKResultCodeToString(code_);
  }

private:
  int code_;
  std::string message_;
};

template <class T>
class CXAPI MTResult {
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
}

#endif
