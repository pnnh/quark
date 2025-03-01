#pragma once
#include <string>
#include <chrono>
#include "quark/types/datetime.hpp"
#include "quark/build.h"

namespace quark
{
    class CXAPI PSFileModel
    {
    public:
        explicit PSFileModel(std::string title);

        std::string URN;
        std::string Title;
        std::string Name;
        std::string Path;
        std::string Keywords;
        std::string Description;
        bool IsDir{};
        bool IsHidden{};
        bool IsIgnore{};
        PSDatetime CreateTime;
        PSDatetime UpdateTime;
    };
}
