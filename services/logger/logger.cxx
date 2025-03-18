
#include <iostream>
#include "quark/services/logger/logger.h"

export module quark.logger;

export class MXLogger {
public:
  MXLogger();

  static void LogInfo(const char *message);
};

MXLogger::MXLogger() = default;

void MXLogger::LogInfo(const char *message) {
  quark::MTLogInfo(message);
}
