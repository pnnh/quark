#pragma once

#include "quark/types/string.h"

#ifdef __cplusplus



extern "C" {
#endif

CXAPI typedef  struct  {
	void *mtSqlSvc;
}QKSqliteService;

CXAPI QKSqliteService * QKSqliteServiceCreate(QKString *message);

CXAPI void QKSqliteServiceDelete(QKSqliteService * instance);

CXAPI QKString *QKSqliteVersion(QKSqliteService * instance);


#ifdef __cplusplus
}
#endif
