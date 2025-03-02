#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI typedef struct PSFileStruct {
    char *URN{};
    char *Title{};
    char *Name{};
    char *Keywords{};
    char *Description{};
    bool IsDir{};
    bool IsHidden{};
    bool IsIgnore{};
} PSFileStruct;

CXAPI PSFileStruct *NewPSFileStruct();

CXAPI void DeletePSFileStruct(PSFileStruct *file);

CXAPI int list_file(int input);

#ifdef __cplusplus
}


#include <string>
#include <chrono>
#include "quark/types/datetime.hpp"

namespace quark {
    class CXAPI PSFileModel {
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


#endif
