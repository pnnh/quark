#pragma once

#include "quark/services/database/sqlite_row.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct
{
    void* mtSqlResult;
} QKSqliteResult;

CXAPI QKSqliteRow* QKSqliteResultGetRow(QKSqliteResult* instance, int index, int* resultCode);

CXAPI int QKSqliteResultGetRowCount(QKSqliteResult* instance, int* resultCode);

#ifdef __cplusplus
}

#include <vector>

namespace quark
{
    class CXAPI MTSqliteResult
    {
    public:
        MTSqliteResult(): rows()
        {
        }

        static QKSqliteResult* MTSqliteResultToQKSqliteResult(std::shared_ptr<MTSqliteResult> instance);
        void appendRow(const std::shared_ptr<MTSqliteRow>& row);

        std::shared_ptr<MTSqliteRow> getRow(int index);

        [[nodiscard]] int getRowCount();

    private:
        std::vector<std::shared_ptr<MTSqliteRow>> rows;
    };
}


#endif
