#include "sqlite_row.h"
#include <algorithm>
#include <utility>

void quark::MTSqliteRow::appendColumn(std::shared_ptr<MTSqliteColumn> column) {
    columnValues[column->getColIndex()] = column;
    colNames.push_back(column->getColName());
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const std::string &&colName) {
    auto indexIt = std::find(colNames.begin(), colNames.end(), colName);

    if (indexIt == colNames.end()) {
        return nullptr;
    }

    auto index = std::distance(colNames.begin(), indexIt);
    return getColumn(static_cast<int>(index));
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(int colIndex) {
    auto it = columnValues.find(colIndex);
    if (it == columnValues.end())
        return nullptr;
    return it->second;
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const char* colName)
{
    auto stdColName = std::string(colName);
    return getColumn(std::move(stdColName));
}

QKSqliteColumn *QKSqliteRowGetColumn(QKSqliteRow *instance, int index) {
    auto mtSqlRow = static_cast<std::shared_ptr<quark::MTSqliteRow >*>(instance->mtSqlRow);
    auto column = (*mtSqlRow)->getColumn(index);
    if (column == nullptr) return nullptr;

    auto qkCol = MTSqliteColumnToQKSqliteColumn(column);
    return qkCol;
}

QKSqliteRow *QKSqliteRowCreate() {
    return new QKSqliteRow();
}

QKSqliteRow *MTSqliteRowToQKSqliteRow(std::shared_ptr<quark::MTSqliteRow> mtSqlRow) {
    auto *qkRow = new QKSqliteRow();
    qkRow->mtSqlRow = new std::shared_ptr(std::move(mtSqlRow));
    return qkRow;
}

QKSqliteColumn *QKSqliteRowGetColumnByName(QKSqliteRow *instance, QKString *name) {
    auto mtSqlRow = static_cast<std::shared_ptr<quark::MTSqliteRow> *>(instance->mtSqlRow);
    auto stdColName = QKStringToStdString(name);
    auto column = (*mtSqlRow)->getColumn(std::move(stdColName));
    if (column == nullptr) return nullptr;
    auto qkCol = MTSqliteColumnToQKSqliteColumn(column);
    return qkCol;
}
