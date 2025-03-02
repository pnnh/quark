module;

#include <iostream>

class QKLogger {
public:
  QKLogger();
  static void LogInfo(const char* message);
};


QKLogger::QKLogger() = default;

void QKLogger::LogInfo(const char *message) {
  std::cout << "QKLogger: " << message << std::endl;
}
