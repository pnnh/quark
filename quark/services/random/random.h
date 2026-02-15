#pragma once

#include "quark/build.h"


#ifdef __cplusplus


#include <string>

namespace quark {
    class PSRandom {
    public:
        static int randomInt(int min, int max);

        static double randomDouble(double min, double max);

        static std::string randomString(int length);
    };
}

extern "C" {
#endif

int MTRandomInt(int min, int max);

#ifdef __cplusplus
}
#endif