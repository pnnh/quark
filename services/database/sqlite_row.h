#pragma once

#include "quark/services/database/sqlite_column.h"
#include "quark/core/types/string.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct
{
    void* mtSqlRow;
} QKSqliteRow;

CXAPI int QKSqliteRowGetColumnCount(QKSqliteRow* instance, int* resultCode);

CXAPI QKSqliteColumn* QKSqliteRowGetColumnByName(QKSqliteRow* instance, QKString* name, int* resultCode);

CXAPI QKSqliteColumn* QKSqliteRowGetColumnByIndex(QKSqliteRow* instance, int index, int* resultCode);

#ifdef __cplusplus
}

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace quark
{
    class MTSqliteRow
    {
    public:
        MTSqliteRow();

        MTSqliteRow(const MTSqliteRow& other) = delete;

        MTSqliteRow& operator=(const MTSqliteRow& other) = delete;

        MTSqliteRow(MTSqliteRow&& other) = delete;

        MTSqliteRow& operator=(MTSqliteRow&& other) = delete;

        void appendColumn(std::shared_ptr<MTSqliteColumn> column);

        std::shared_ptr<MTSqliteColumn> getColumn(const std::string&& colName);

        std::shared_ptr<MTSqliteColumn> getColumn(int colIndex);

        std::shared_ptr<MTSqliteColumn> getColumn(const char* colName);

        std::shared_ptr<MTSqliteColumn> getColumn(const std::string& colName);

        int getColumnCount();

        std::shared_ptr<std::vector<std::string>> getColumnNames();

        std::shared_ptr<std::vector<MTSqliteValue>> getRowValues();
        static QKSqliteRow* MTSqliteRowToQKSqliteRow(std::shared_ptr<quark::MTSqliteRow> mtSqlRow);

    private:
        std::shared_ptr<std::vector<std::string>> colNames;
        std::map<int, std::shared_ptr<MTSqliteColumn>> columnValues;
    };
}


#endif
