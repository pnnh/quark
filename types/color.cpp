#include "color.h"
#include "quark/services/random/random.hpp"

namespace quark
{
    MTColor::MTColor() : r(0), g(0), b(0), a(0)
    {
    }

    MTColor::MTColor(int r, int g, int b) : r(r), g(g), b(b), a(255)
    {
    }

    MTColor::MTColor(int r, int g, int b, int a) : r(r), g(g), b(b), a(a)
    {
    }

    MTColor MTColor::randomColor()
    {
        int r = PSRandom::randomInt(0, 255);
        int g = PSRandom::randomInt(0, 255);
        int b = PSRandom::randomInt(0, 255);
        return {r, g, b};
    }

    MTColor MTColor::FromArgb(int a, int r, int g, int b)
    {
        return {r, g, b, a};
    }

    const MTColor MTColor::White = MTColor(255, 255, 255);
    const MTColor MTColor::Black = MTColor(0, 0, 0);
    const MTColor MTColor::Red = MTColor(255, 0, 0);
    const MTColor MTColor::Green = MTColor(0, 255, 0);
    const MTColor MTColor::Blue = MTColor(0, 0, 255);
    const MTColor MTColor::Yellow = MTColor(255, 255, 0);
    const MTColor MTColor::Cyan = MTColor(0, 255, 255);
    const MTColor MTColor::Magenta = MTColor(255, 0, 255);
}
