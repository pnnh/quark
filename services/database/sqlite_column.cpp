#include "sqlite_column.h"

#include <sqlite3.h>

#include "quark/types/Exception.h"


quark::MTSqliteColumn::MTSqliteColumn() : colType(), colIndex() {
}

quark::MTSqliteColumn::MTSqliteColumn(const int colType, const int colIndex,
                                      const std::string &&colName) : colType(colType), colIndex(colIndex),
                                                                     colName(colName) {
    if (colIndex < 0) throw quark::PSException("列索引必须大于等于0");
}

quark::MTSqliteColumn::~MTSqliteColumn() {
}

quark::MTSqliteColumn::MTSqliteColumn(const MTSqliteColumn &other) : colType(other.colType), colIndex(other.colIndex),
                                                                     colName(other.colName),
                                                                     colIsNull(other.colIsNull) {
    // if (colType == SQLITE_TEXT)
    // {
    //     stringValue = other.stringValue;
    // }
    // else if (colType == SQLITE_INTEGER)
    // {
    //     intValue = other.intValue;
    // }
    // else if (colType == SQLITE_FLOAT)
    // {
    //     floatValue = other.floatValue;
    // }
    variantValue = other.variantValue;
}

quark::MTSqliteColumn &quark::MTSqliteColumn::operator=(const MTSqliteColumn &other) {
    colType = other.colType;
    colIndex = other.colIndex;
    colName = other.colName;
    colIsNull = other.colIsNull;
    // if (colType == SQLITE_TEXT)
    // {
    //     stringValue = other.stringValue;
    // }
    // else if (colType == SQLITE_INTEGER)
    // {
    //     intValue = other.intValue;
    // }
    // else if (colType == SQLITE_FLOAT)
    // {
    //     floatValue = other.floatValue;
    // }
    variantValue = other.variantValue;
    return *this;
}

quark::MTSqliteColumn::MTSqliteColumn(MTSqliteColumn &&other) noexcept : colType(other.colType),
                                                                         colIndex(other.colIndex),
                                                                         colName(std::move(other.colName)),
                                                                         colIsNull(other.colIsNull) {
    // if (colType == SQLITE_TEXT)
    // {
    //     stringValue = std::move(other.stringValue);
    // }
    // else if (colType == SQLITE_INTEGER)
    // {
    //     intValue = other.intValue;
    // }
    // else if (colType == SQLITE_FLOAT)
    // {
    //     floatValue = other.floatValue;
    // }
    variantValue = std::move(other.variantValue);
}

quark::MTSqliteColumn &quark::MTSqliteColumn::operator=(MTSqliteColumn &&other) noexcept {
    colType = other.colType;
    colIndex = other.colIndex;
    colName = std::move(other.colName);
    colIsNull = other.colIsNull;

    // if (colType == SQLITE_TEXT)
    // {
    //     stringValue = std::move(other.stringValue);
    // }
    // else if (colType == SQLITE_INTEGER)
    // {
    //     intValue = other.intValue;
    // }
    // else if (colType == SQLITE_FLOAT)
    // {
    //     floatValue = other.floatValue;
    // }
    variantValue = std::move(other.variantValue);
    other.colType = 0;
    other.colIndex = 0;
    other.colName.clear();
    other.colIsNull = false;
    // other.stringValue.clear();
    // other.intValue = 0;
    // other.floatValue = 0;
    return *this;
}

int quark::MTSqliteColumn::getColIndex() const {
    return colIndex;
}

std::string quark::MTSqliteColumn::getColName() const {
    if (colName.empty()) return "column" + std::to_string(colIndex);
    return colName;
}

std::string quark::MTSqliteColumn::getStringValue() const {
    return variantValue.index() == 0 ? std::get<std::string>(variantValue) : "";
}

void quark::MTSqliteColumn::setStringValue(const char *value) {
    // stringValue = value;
    variantValue = std::string(value);
}

void quark::MTSqliteColumn::setStringValue(const std::string &value) {
    // stringValue = value;
    variantValue = value;
}

void quark::MTSqliteColumn::setStringValue(const std::string &&value) {
    // stringValue = value;
    variantValue = value;
}

int quark::MTSqliteColumn::getIntValue() const {
    // return intValue;
    return variantValue.index() == 1 ? static_cast<int>(std::get<long>(variantValue)) : 0;
}

void quark::MTSqliteColumn::setIntValue(int value) {
    // intValue = value;
    variantValue = static_cast<long>(value);
}

double quark::MTSqliteColumn::getFloatValue() const {
    // return floatValue;
    return variantValue.index() == 2 ? std::get<double>(variantValue) : 0;
}

void quark::MTSqliteColumn::setFloatValue(double value) {
    // floatValue = value;
    variantValue = value;
}


int quark::MTSqliteColumn::getColType() const {
    return colType;
}

bool quark::MTSqliteColumn::isNull() const {
    return colIsNull;
}

void quark::MTSqliteColumn::setNull() {
    colIsNull = true;
}

int QKSQliteColumnGetIntValue(QKSqliteColumn *instance) {
    auto mtSqlCol = static_cast<quark::MTSqliteColumn *>(instance->mtSqliteColumn);
    return mtSqlCol->getIntValue();
}

QKString *QKSQliteColumnGetStringValue(QKSqliteColumn *instance) {
    auto mtSqlCol = static_cast<quark::MTSqliteColumn *>(instance->mtSqliteColumn);
    auto stringValue = mtSqlCol->getStringValue();
    return StdStringToQKStringPtr(stringValue);
}

QKSqliteColumn *QKSqliteColumnCreate() {
    return new QKSqliteColumn();
}

QKSqliteColumn *MTSqliteColumnToQKSqliteColumn(const quark::MTSqliteColumn &mtSqlCol) {
    auto newMtRow = new quark::MTSqliteColumn(mtSqlCol);
    auto qkCol = new QKSqliteColumn();
    qkCol->mtSqliteColumn = newMtRow;
    return qkCol;
}
