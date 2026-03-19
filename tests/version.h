#pragma once

#include "quark/quark.h"

#ifdef __cplusplus

extern "C" {
#endif

void cSqliteVersion();

void cSqliteSelectNames();

void cSqliteStatParams();

#ifdef __cplusplus
}

void cxxSqliteStatParams();

#endif