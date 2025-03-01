#pragma once

#include "quark/build.h"

CXAPI typedef struct PSFileStruct
{
    char* URN{};
    char* Title{};
    char* Name{};
    char* Keywords{};
    char* Description{};
    bool IsDir{};
    bool IsHidden{};
    bool IsIgnore{};
} PSFileStruct;

CXAPI PSFileStruct* NewPSFileStruct();
CXAPI void DeletePSFileStruct(PSFileStruct* file);
CXAPI int list_file(int input);

