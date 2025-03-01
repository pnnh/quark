#include "SqliteResult.h"

void quark::MTSqliteResult::appendRow(const MTSqliteRow &&row) {
    rows.push_back(row);
}

std::optional<quark::MTSqliteRow> quark::MTSqliteResult::getRow(int index) {
    if (index < 0 || index >= rows.size()) return std::nullopt;
    return rows[index];
}

unsigned int quark::MTSqliteResult::getRowCount() const {
    return this->rows.size();
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteResult::getColumn(int rowIndex, int colIndex) {
    auto sqlRow = getRow(rowIndex);
    if (!sqlRow.has_value()) return std::nullopt;
    return sqlRow.value().getColumn(colIndex);
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteResult::getColumn(int rowIndex, const char *colName) {
    return getColumn(rowIndex, std::string(colName));
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteResult::getColumn(int rowIndex,
                                                                      const std::string &colName) {
    return getColumn(rowIndex, std::move(colName));
}

std::optional<quark::MTSqliteColumn> quark::MTSqliteResult::getColumn(int rowIndex,
                                                                      const std::string &&colName) {
    auto sqlRow = getRow(rowIndex);
    if (!sqlRow.has_value()) return std::nullopt;
    return sqlRow.value().getColumn(static_cast<std::string>(colName));
}
