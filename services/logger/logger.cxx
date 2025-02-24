module;

#include <iostream>

module quark.logger;

QKLogger::QKLogger() = default;

void QKLogger::LogInfo(const char *message) {
  std::cout << "QKLogger: " << message << std::endl;
}
