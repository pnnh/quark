#include "version.h"
#include "string.h"
#include <stdio.h>

#include <quark/services/database/SqliteService.h>
#include "quark/types/string.h"

void cSqliteVersion() {
    const char *database_path = "polaris.sqlite";
    QKString *dbPath = QKStringCreate((char *) database_path);
    QKSqliteService *sqliteService = QKSqliteServiceCreate(dbPath);
    QKString *version = QKSqliteVersion(sqliteService);

    char *verStr = QKStringGetData(version);
    printf("cSqliteVersion: %s\n", verStr);
}

void cSqliteSelectNames() {
    const char *database_path = "polaris.sqlite";
    QKString *dbPath = QKStringCreate((char *) database_path);
    QKSqliteService *sqliteService = QKSqliteServiceCreate(dbPath);
    QKString *sqlText = QKStringCreate("SELECT 'hello呀哈哈' as strVal, 128 as intVal;");
    QKSqliteResult *sqlResult = QKSqliteRunSql(sqliteService, sqlText);
    QKSqliteRow *sqlRow = QKSqliteResultGetRow(sqlResult, 0);
    QKSqliteColumn *strCol = QKSqliteRowGetColumn(sqlRow, 0);
    QKString *strVal = QKSQliteColumnGetStringValue(strCol);
    char *strValData = QKStringGetData(strVal);
    QKSqliteColumn *intCol = QKSqliteRowGetColumn(sqlRow, 1);
    int intVal = QKSQliteColumnGetIntValue(intCol);

    printf("cSqliteSelectNames: %s, %d\n", strValData, intVal);
}
