#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void * itemValue;
    void * nextItem;
} QKListItem;

typedef struct {
    QKListItem * listItem;
    int length;
} QKList;

#ifdef __cplusplus
}
#endif
