#include "sqlite_row.h"
#include <algorithm>
#include <utility>

quark::MTSqliteRow::MTSqliteRow(): colNames(std::make_shared<std::vector<std::string> >()) {
}

void quark::MTSqliteRow::appendColumn(std::shared_ptr<MTSqliteColumn> column) {
    columnValues[column->getColIndex()] = column;
    colNames->push_back(column->getColName());
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const std::string &&colName) {
    auto indexIt = std::find(colNames->begin(), colNames->end(), colName);

    if (indexIt == colNames->end()) {
        return nullptr;
    }

    auto index = std::distance(colNames->begin(), indexIt);
    return getColumn(static_cast<int>(index));
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(int colIndex) {
    auto it = columnValues.find(colIndex);
    if (it == columnValues.end())
        return nullptr;
    return it->second;
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const char *colName) {
    auto stdColName = std::string(colName);
    return getColumn(std::move(stdColName));
}

std::shared_ptr<quark::MTSqliteColumn> quark::MTSqliteRow::getColumn(const std::string &colName) {
    return getColumn(std::move(colName));
}

int quark::MTSqliteRow::getColumnCount() {
    return colNames->size();
}

std::shared_ptr<std::vector<std::string> > quark::MTSqliteRow::getColumnNames() {
    return colNames;
}

std::shared_ptr<std::vector<quark::MTSqliteValue> > quark::MTSqliteRow::getRowValues() {
    std::shared_ptr<std::vector<quark::MTSqliteValue> > values;
    for (const auto &colName: *colNames) {
        auto col = getColumn(colName);
        values->push_back(col->getVariantValue());
    }
    return values;
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

int QKSqliteRowGetColumnCount(QKSqliteRow *instance) {
    auto mtSqlRow = static_cast<std::shared_ptr<quark::MTSqliteRow> *>(instance->mtSqlRow);
    return static_cast<int>((*mtSqlRow)->getColumnCount());
}

QKSqliteColumn *QKSqliteRowGetColumnByIndex(QKSqliteRow *instance, int index) {
    auto mtSqlRow = static_cast<std::shared_ptr<quark::MTSqliteRow> *>(instance->mtSqlRow);
    auto column = (*mtSqlRow)->getColumn(index);
    if (column == nullptr) return nullptr;
    auto qkCol = MTSqliteColumnToQKSqliteColumn(column);
    return qkCol;
}
