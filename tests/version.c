#include "version.h"
#include "string.h"
#include <stdio.h>

#include <quark/services/database/sqlite_service.h>
#include "quark/core/types/string.h"

void cSqliteVersion()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath, nullptr);
    QKString* version = QKSqliteVersion(sqliteService, nullptr);
    QKSqliteServiceDelete(sqliteService, nullptr);
    char* verStr = QKStringGetData(version);
    printf("cSqliteVersion: %s\n", verStr);
}

void cSqliteSelectNames()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath, nullptr);
    QKString* sqlText = QKStringCreate("SELECT 'hello呀哈哈' as strVal, 128 as intVal;");
    QKSqliteResult* sqlResult = QKSqliteRunSql(sqliteService, sqlText, nullptr);
    QKSqliteRow* sqlRow = QKSqliteResultGetRow(sqlResult, 0, nullptr);
    QKSqliteColumn* strCol = QKSqliteRowGetColumnByIndex(sqlRow, 0, nullptr);
    QKString* strVal = QKSQliteColumnGetStringValue(strCol, nullptr);
    char* strValData = QKStringGetData(strVal);
    QKSqliteColumn* intCol = QKSqliteRowGetColumnByIndex(sqlRow, 1, nullptr);
    int intVal = QKSQliteColumnGetIntValue(intCol, nullptr);

    QKString* strColName = QKStringCreate("strVal");
    QKSqliteColumn* strColByName = QKSqliteRowGetColumnByName(sqlRow, strColName, nullptr);
    QKString* strValByName = QKSQliteColumnGetStringValue(strColByName, nullptr);

    QKSqliteColumn* intColByName = QKSqliteRowGetColumnByName(sqlRow, QKStringCreate("intVal"), nullptr);
    int intValByName = QKSQliteColumnGetIntValue(intColByName, nullptr);

    QKSqliteServiceDelete(sqliteService, nullptr);
    printf("cSqliteSelectNames: %s, %d\n\t%s, %d\n", strValData, intVal, QKStringGetData(strValByName), intValByName);
}

void cSqliteStatParams()
{
    const char* database_path = "polaris.sqlite";
    QKString* dbPath = QKStringCreate((char*)database_path);
    QKSqliteService* sqliteService = QKSqliteServiceCreate(dbPath, nullptr);
    QKString* sqlText = QKStringCreate("SELECT $str as strVal, $int as intVal;");
    QKSqliteCommand* sqlCmd = QKSqliteServiceCreateCommand(sqliteService, sqlText, nullptr);
    QKString* strName = QKStringCreate("$str");
    QKString* strVal = QKStringCreate("hello呀哈哈");
    int rc = QKSqliteCommandBindString(sqlCmd, strName, strVal, nullptr);
    if (rc != 0)
    {
        printf("cSqliteStatParams error: %d\n", rc);
        return;
    }

    QKString* intName = QKStringCreate("$int");
    int intVal = 128;
    QKSqliteCommandBindInt(sqlCmd, intName, intVal, nullptr);

    QKSqliteResult* sqlResult = QKSqliteCommandRun(sqlCmd, nullptr);
    QKSqliteRow* sqlRow = QKSqliteResultGetRow(sqlResult, 0, nullptr);

    QKString* strColName = QKStringCreate("strVal");
    QKSqliteColumn* strColByName = QKSqliteRowGetColumnByName(sqlRow, strColName, nullptr);
    QKString* strValByName = QKSQliteColumnGetStringValue(strColByName, nullptr);
    char* strValData = QKStringGetData(strValByName);
    QKSqliteColumn* intColByName = QKSqliteRowGetColumnByName(sqlRow, QKStringCreate("intVal"), nullptr);
    int intValByName = QKSQliteColumnGetIntValue(intColByName, nullptr);

    // QKSqliteCommandClose(sqlCmd);
    // QKSqliteServiceDelete(sqliteService);
    printf("cSqliteSelectNames: %s, %d\n", strValData, intValByName);
}
