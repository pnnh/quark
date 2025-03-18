#pragma once

namespace quark
{
    enum codes { Ok = 200, Error = 500 };

    const char * CodeMessage(int code);
}