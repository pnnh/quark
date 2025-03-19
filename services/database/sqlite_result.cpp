#include "sqlite_result.h"

#include <quark/infra/result/result.h>

void quark::MTSqliteResult::appendRow(const std::shared_ptr<MTSqliteRow>& row)
{
    rows.push_back(row);
}

std::shared_ptr<quark::MTSqliteRow> quark::MTSqliteResult::getRow(int index)
{
    if (index < 0 || index >= rows.size()) return nullptr;
    return rows[index];
}

int quark::MTSqliteResult::getRowCount()
{
    return (int)this->rows.size();
}

QKSqliteResult* quark::MTSqliteResult::MTSqliteResultToQKSqliteResult(std::shared_ptr<MTSqliteResult> instance)
{
    auto qkResult = new QKSqliteResult{};
    qkResult->mtSqlResult = new std::shared_ptr<MTSqliteResult>{instance};
    return qkResult;
}

QKSqliteRow* QKSqliteResultGetRow(QKSqliteResult* instance, int index, int* resultCode)
{
    auto mtSqlResult = static_cast<std::shared_ptr<quark::MTSqliteResult>*>(instance->mtSqlResult);
    auto row = (*mtSqlResult)->getRow(index);
    if (row == nullptr) return nullptr;
    auto qkRow = quark::MTSqliteRow::MTSqliteRowToQKSqliteRow(row);
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return qkRow;
}

int QKSqliteResultGetRowCount(QKSqliteResult* instance, int* resultCode)
{
    auto mtSqlResult = static_cast<std::shared_ptr<quark::MTSqliteResult>*>(instance->mtSqlResult);
    if (mtSqlResult == nullptr) return 0;
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return (*mtSqlResult)->getRowCount();
}
