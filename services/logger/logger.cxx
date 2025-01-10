module;

#include <iostream>
#include "quark/build.h"

export module quark.logger;

export class MTCXXAPI MTLogger {
public:
  MTLogger();
  static void MTLogInfo(const char* message);
};

MTLogger::MTLogger() = default;

void MTLogger::MTLogInfo(const char* message) {
  std::cout << "MTLogInfo: " << message << std::endl;
}