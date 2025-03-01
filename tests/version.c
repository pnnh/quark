#include "version.h"
#include "string.h"
#include <stdio.h>

#include <quark/services/database/SqliteService.h>
#include "quark/types/string.h"

void cSqliteVersion() {
    const char *database_path = "polaris.sqlite";
    QKString *dbPath = QKStringCreateWithLength((char *) database_path, strlen(database_path));
    QKSqliteService *sqliteService = QKSqliteServiceCreate(dbPath);
    QKString *version = QKSqliteVersion(sqliteService);

    printf("cSqliteVersion: %s", version->data);
}

void cSqliteSelectNames() {
    const char *database_path = "polaris.sqlite";
    QKString *dbPath = QKStringCreateWithLength((char *) database_path, strlen(database_path));
    QKSqliteService *sqliteService = QKSqliteServiceCreate(dbPath);
    QKString *sqlText = QKStringCreate("SELECT 'hello呀哈哈' as strVal, 128 as intVal;");
    QKSqliteResult *sqlResult = QKSqliteRunSql(sqliteService, sqlText);
    QKSqliteRow *sqlRow = QKSqliteResultGetRow(sqlResult, 0);
    QKSqliteColumn *strCol = QKSqliteRowGetColumn(sqlRow, 0);
    QKString *strVal = QKSQliteColumnGetStringVaule(strCol);
    QKSqliteColumn *intCol = QKSqliteRowGetColumn(sqlRow, 1);
    int intVal = QKSQliteColumnGetIntVaule(intCol);

    printf("cSqliteSelectNames: %s, %d", strVal->data, intVal);
}
