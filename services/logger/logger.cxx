export module quark.logger;

#include <iostream>

export class CXLogger {
public:
  CXLogger();

  static void LogInfo(const char *message);
};

CXLogger::CXLogger() = default;

void CXLogger::LogInfo(const char *message) {
  std::cout << "CXLogger: " << message << std::endl;
}
