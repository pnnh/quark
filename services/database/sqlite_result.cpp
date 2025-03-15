#include "sqlite_result.h"

void quark::MTSqliteResult::appendRow(const std::shared_ptr<MTSqliteRow> &row) {
    rows.push_back(row);
}

std::shared_ptr<quark::MTSqliteRow> quark::MTSqliteResult::getRow(int index) {
    if (index < 0 || index >= rows.size()) return nullptr;
    return rows[index];
}

int quark::MTSqliteResult::getRowCount() {
    return (int) this->rows.size();
}

QKSqliteRow *QKSqliteResultGetRow(QKSqliteResult *instance, int index) {
    auto mtSqlResult = static_cast<quark::MTSqliteResult *>(instance->mtSqlResult);
    auto row = mtSqlResult->getRow(index);
    if (row == nullptr) return nullptr;
    auto qkRow = MTSqliteRowToQKSqliteRow(row);
    return qkRow;
}

QKSqliteResult *MTSqliteResultToQKSqliteResult(quark::MTSqliteResult *instance) {
    auto qkResult = new QKSqliteResult{};
    qkResult->mtSqlResult = instance;
    return qkResult;
}

int QKSqliteResultGetRowCount(QKSqliteResult *instance) {
    auto mtSqlResult = static_cast<quark::MTSqliteResult *>(instance->mtSqlResult);
    if (mtSqlResult == nullptr) return 0;
    return mtSqlResult->getRowCount();
}
