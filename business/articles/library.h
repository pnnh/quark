#pragma once
#include <vector>
#include <quark/business/models/articles/location.h>

namespace quark
{
    bool isLibraryDirectory(const std::string& directoryName);

    class LibraryServerBusiness
    {
    public:
        explicit LibraryServerBusiness(const std::string& baseUrl);

        [[nodiscard]] std::shared_ptr<std::vector<quark::PSLocationModel>> selectLibraries() const;

    private:
        std::string baseUrl;
    };
}
