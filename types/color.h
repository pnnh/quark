#pragma once

#include "quark/build.h"

#ifdef __cplusplus


namespace quark
{
    class MTAPI MTColor
    {
    public:
        MTColor();
        MTColor(int r, int g, int b);
        MTColor(int r, int g, int b, int a);

        static const MTColor White;
        static const MTColor Black;
        static const MTColor Red;
        static const MTColor Green;
        static const MTColor Blue;
        static const MTColor Yellow;
        static const MTColor Cyan;
        static const MTColor Magenta;

        static MTColor FromArgb(int a, int r, int g, int b);
        static MTColor randomColor();

        int r;
        int g;
        int b;
        int a;
    };
}

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
