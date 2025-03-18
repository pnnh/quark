#include "version.h"
#include "string.h"
#include <stdio.h>

#include <quark/services/database/sqlite_service.h>
#include "quark/core/types/string.h"

void cSqliteVersion()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath);
    QKString* version = QKSqliteVersion(sqliteService);
    QKSqliteServiceDelete(sqliteService);
    char* verStr = QKStringGetData(version);
    printf("cSqliteVersion: %s\n", verStr);
}

void cSqliteSelectNames()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath);
    QKString* sqlText = QKStringCreate("SELECT 'hello呀哈哈' as strVal, 128 as intVal;");
    QKSqliteResult* sqlResult = QKSqliteRunSql(sqliteService, sqlText);
    QKSqliteRow* sqlRow = QKSqliteResultGetRow(sqlResult, 0);
    QKSqliteColumn* strCol = QKSqliteRowGetColumnByIndex(sqlRow, 0);
    QKString* strVal = QKSQliteColumnGetStringValue(strCol);
    char* strValData = QKStringGetData(strVal);
    QKSqliteColumn* intCol = QKSqliteRowGetColumnByIndex(sqlRow, 1);
    int intVal = QKSQliteColumnGetIntValue(intCol);

    QKString* strColName = QKStringCreate("strVal");
    QKSqliteColumn* strColByName = QKSqliteRowGetColumnByName(sqlRow, strColName);
    QKString* strValByName = QKSQliteColumnGetStringValue(strColByName);

    QKSqliteColumn* intColByName = QKSqliteRowGetColumnByName(sqlRow, QKStringCreate("intVal"));
    int intValByName = QKSQliteColumnGetIntValue(intColByName);

    QKSqliteServiceDelete(sqliteService);
    printf("cSqliteSelectNames: %s, %d\n\t%s, %d\n", strValData, intVal, QKStringGetData(strValByName), intValByName);
}

void cSqliteStatParams()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath);
    QKString* sqlText = QKStringCreate("SELECT $str as strVal, $int as intVal;");
    QKSqliteCommand* sqlCmd = QKSqliteServiceCreateCommand(sqliteService, sqlText);
    QKString* strName = QKStringCreate("$str");
    QKString* strVal = QKStringCreate("hello呀哈哈");
    int rc = QKSqliteCommandBindString(sqlCmd, strName, strVal);
    if (rc != 0)
    {
        printf("cSqliteStatParams error: %d\n", rc);
        return;
    }

    QKString* intName = QKStringCreate("$int");
    int intVal = 128;
    QKSqliteCommandBindInt(sqlCmd, intName, intVal);

    QKSqliteResult* sqlResult = QKSqliteCommandRun(sqlCmd);
    QKSqliteRow* sqlRow = QKSqliteResultGetRow(sqlResult, 0);

    QKString* strColName = QKStringCreate("strVal");
    QKSqliteColumn* strColByName = QKSqliteRowGetColumnByName(sqlRow, strColName);
    QKString* strValByName = QKSQliteColumnGetStringValue(strColByName);
    char* strValData = QKStringGetData(strValByName);
    QKSqliteColumn* intColByName = QKSqliteRowGetColumnByName(sqlRow, QKStringCreate("intVal"));
    int intValByName = QKSQliteColumnGetIntValue(intColByName);

    // QKSqliteCommandClose(sqlCmd);
    // QKSqliteServiceDelete(sqliteService);
    printf("cSqliteSelectNames: %s, %d\n", strValData, intValByName);
}
