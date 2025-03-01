#pragma once

#include "quark/services/database/SqliteRow.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct {
    void *mtSqlResult;
} QKSqliteResult;

QKSqliteRow *QKSqliteResultGetRow(QKSqliteResult *instance, int index);

#ifdef __cplusplus
}

#include <vector>

namespace quark {
    class MTSqliteResult {
    public:
        MTSqliteResult(): rows() {
        }

        void appendRow(const MTSqliteRow &&row);

        std::optional<MTSqliteRow> getRow(int index);

        [[nodiscard]] unsigned int getRowCount() const;

        std::optional<MTSqliteColumn> getColumn(int rowIndex, int colIndex);

        std::optional<MTSqliteColumn> getColumn(int rowIndex, const char *colName);

        std::optional<MTSqliteColumn> getColumn(int rowIndex, const std::string &colName);

        std::optional<MTSqliteColumn> getColumn(int rowIndex, const std::string &&colName);

    private:
        std::vector<MTSqliteRow> rows;
    };
}

#endif
