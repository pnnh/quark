#pragma once

#include <string>

namespace quark {
    class PSRandom
    {
    public:
        static int randomInt(int min, int max);
        static double randomDouble(double min, double max);
        static std::string randomString(int length);
    };
}