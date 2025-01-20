
#include <string>
#include <chrono>
#include "quark/types/datetime.hpp"

namespace quark
{
    class PSChannelModel
    {
    public:
        explicit PSChannelModel();
        explicit PSChannelModel(const std::string& name);

        std::string URN;
        std::string Name;
        std::string Title;
        std::string Keywords;
        std::string Description;
        std::string Image;
        std::string Path;
        quark::PSDatetime CreateTime;
        quark::PSDatetime UpdateTime;
    };
}
