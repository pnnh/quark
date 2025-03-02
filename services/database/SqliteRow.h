#pragma once

#include "quark/services/database/SqliteColumn.h"
#include "quark/types/string.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtSqlRow;
} QKSqliteRow;

QKSqliteColumn *QKSqliteRowGetColumn(QKSqliteRow *instance, int index);

QKSqliteRow *QKSqliteRowCreate();

#ifdef __cplusplus
}

#include <iostream>
#include <map>
#include <optional>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace quark {
    class MTSqliteRow {
    public:
        void appendColumn(const MTSqliteColumn &&column);

        std::optional<MTSqliteColumn> getColumn(const std::string &&colName);

        std::optional<MTSqliteColumn> getColumn(int colIndex);

    private:
        std::vector<std::string> colNames;
        std::map<int, MTSqliteColumn> columnValues;
    };
}

QKSqliteRow *MTSqliteRowToQKSqliteRow(const quark::MTSqliteRow &mtSqlRow);

#endif
