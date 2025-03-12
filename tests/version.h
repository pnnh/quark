#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI void cSqliteVersion();

CXAPI void cSqliteSelectNames();

CXAPI void cSqliteStatParams();

#ifdef __cplusplus
}

CXAPI void cxxSqliteStatParams();

#endif

