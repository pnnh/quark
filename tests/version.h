#pragma once

#include "quark/quark.h"

#ifdef __cplusplus

extern "C" {
#endif

QKAPI void cSqliteVersion();

QKAPI void cSqliteSelectNames();

QKAPI void cSqliteStatParams();

#ifdef __cplusplus
}

QKAPI void cxxSqliteStatParams();

#endif