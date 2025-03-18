#pragma once
#include <vector>
#include <quark/business/models/articles/Library.h>

namespace quark
{
    bool isLibraryDirectory(const std::string& directoryName);

    class LibraryServerBusiness
    {
    public:
        explicit LibraryServerBusiness(const std::string& baseUrl);

        [[nodiscard]] std::shared_ptr<std::vector<quark::PSLibraryModel>> selectLibraries() const;

    private:
        std::string baseUrl;
    };
}
