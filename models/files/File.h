#pragma once

#include "quark/build.h"

MTCAPI typedef struct PSFileStruct
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

MTCAPI PSFileStruct* NewPSFileStruct();
MTCAPI void DeletePSFileStruct(PSFileStruct* file);
MTCAPI int list_file(int input);

