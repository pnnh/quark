#include "SqliteRow.h"
#include <algorithm>

void quark::MTSqliteRow::appendColumn(const quark::MTSqliteColumn &&column) {
    columnValues[column.getColIndex()] = column;
    colNames.push_back(column.getColName());
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const std::string &&colName) {
    auto indexIt = std::find(colNames.begin(), colNames.end(), colName);

    if (indexIt == colNames.end()) {
        return std::nullopt;
    }

    auto index = std::distance(colNames.begin(), indexIt);
    return getColumn(static_cast<int>(index));
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(int colIndex) {
    auto it = columnValues.find(colIndex);
    if (it == columnValues.end())
        return std::nullopt;
    return it->second;
}

QKSqliteColumn *QKSqliteRowGetColumn(QKSqliteRow *instance, int index) {
    auto mtSqlRow = static_cast<quark::MTSqliteRow *>(instance->mtSqlRow);
    auto column = mtSqlRow->getColumn(index);
    if (!column.has_value()) return nullptr;

    auto qkCol = MTSqliteColumnToQKSqliteColumn(column.value());
    return qkCol;
}

QKSqliteRow *QKSqliteRowCreate() {
    return new QKSqliteRow();
}

QKSqliteRow *MTSqliteRowToQKSqliteRow(const quark::MTSqliteRow &mtSqlRow) {
    auto newMtRow = new quark::MTSqliteRow(mtSqlRow);
    auto *qkRow = new QKSqliteRow();
    qkRow->mtSqlRow = newMtRow;
    return qkRow;
}
