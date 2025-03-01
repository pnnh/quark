#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI typedef struct  {
    char *data;
    size_t length;
}QKString;

CXAPI QKString* QKStringCreate(char *data, size_t length);


#ifdef __cplusplus
}
#endif
