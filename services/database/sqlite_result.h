#pragma once

#include "quark/services/database/sqlite_row.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct {
    void *mtSqlResult;
} QKSqliteResult;

CXAPI QKSqliteRow *QKSqliteResultGetRow(QKSqliteResult *instance, int index);

CXAPI int QKSqliteResultGetRowCount(QKSqliteResult *instance);

#ifdef __cplusplus
}

#include <vector>

namespace quark {
    class MTSqliteResult {
    public:
        MTSqliteResult(): rows() {
        }

        void appendRow(const std::shared_ptr<MTSqliteRow> &row);

        std::shared_ptr<MTSqliteRow> getRow(int index);

        [[nodiscard]] int getRowCount();

    private:
        std::vector<std::shared_ptr<MTSqliteRow> > rows;
    };
}

QKSqliteResult *MTSqliteResultToQKSqliteResult(quark::MTSqliteResult *instance);

#endif
