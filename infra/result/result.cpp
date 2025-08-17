#include "result.h"

constexpr const char *QKResultCodeToString(int qkCode) {
  switch (qkCode) {
    case QKResultOk:
      return "OK";
    case QKResultError:
      return "ERROR";
    default:
      return "UNKNOWN";
  }
}

quark::MTException::MTException() : code_(QKResultError) {
}

quark::MTException::MTException(const int &code)
  : code_(code) {
}

quark::MTException::MTException(const std::string &message) :
  code_(QKResultError),
  message_(message) {
}

quark::MTException::MTException(const int &code, const std::string &message)
  : code_(code), message_(message) {
}

void quark::MTException::appendMessage(const std::string &message) {
  message_ = message_ + message;
}

int quark::MTException::code() {
  return code_;
}

const std::string quark::MTException::message() {
  return message_;
}
